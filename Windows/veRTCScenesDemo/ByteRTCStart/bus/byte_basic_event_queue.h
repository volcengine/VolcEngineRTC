/*
 *  Copyright (c) 2020 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief event queue
 */

#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <list>
#include <condition_variable>
#include <chrono>
#include "byte_basic_string_util.h"

namespace bytertc {
namespace basic {

/**
 * @brief 事件池，使用condition_variable和list实现信号量机制
*/
template < class Item >
class EventQueue
{
public:
    enum {
        kNoEvent                        = 0,    // timedout
        kGetEvent                       = 1,    // do fetch event from the pool
        kBroken                         = 2,    // the waiting progress has been broken
        kInterrupt                      = 3
    };

    typedef std::chrono::nanoseconds        IntervalType;
    typedef std::function< bool() >         status_t;
    typedef std::function< void() >         breaker_t;
    typedef std::function< void(Item&) >    handler_t;
public:
    EventQueue<Item>() : validate_(false) { }
    ~EventQueue<Item>(){
        std::lock_guard<std::mutex> _l(locker_);
        while ( !event_queue_.empty() ) event_queue_.clear();
        validate_ = false;
        cv_.notify_all();
    }

    size_t Wait( Item& container, status_t interrupt = nullptr ) {
        std::unique_lock<std::mutex> _l(locker_);
        if ( !validate_ ) {
            // Check if have unprocessed event
            if ( event_queue_.size() == 0 ) return kBroken;
            container = std::move(event_queue_.front());
            event_queue_.pop_front();
            return kGetEvent;
        }
        bool _is_interrupted = false;
        cv_.wait(_l, [this, interrupt, &_is_interrupted](){
            _is_interrupted = (interrupt ? interrupt() : false);
            return (
                // If not validate, then means the pool has been broken, need return true
                !validate_ ||
                // If return true, means current waiting thread has been broken
                _is_interrupted ||
                // Has event incoming, wake up.
                event_queue_.size() > 0
                );
        });

        if ( _is_interrupted ) return kInterrupt;
        if ( event_queue_.size() > 0 ) {
            container = std::move(event_queue_.front());
            event_queue_.pop_front();
            return kGetEvent;
        }
        return kBroken;
    }

    size_t WaitFor(IntervalType d, Item& container, status_t interrupt = nullptr) {
        std::unique_lock<std::mutex> _l(locker_);
        if ( !validate_ ) {
            if ( event_queue_.size() == 0 ) return kBroken;
            container = std::move(event_queue_.front());
            event_queue_.pop_front();
            return kGetEvent;
        }
        bool _is_interrupted = false;
        bool _result = cv_.wait_for(_l, d, [this, interrupt, &_is_interrupted](){
            _is_interrupted = (interrupt ? interrupt() : false);
            return (
                // If not validate, then means the pool has been broken, need return true
                !validate_ ||
                // If return true, means current waiting thread has been broken
                _is_interrupted ||
                // Has event incoming, wake up.
                event_queue_.size() > 0
                );
        });
        // Timedout
        if ( !_result ) return kNoEvent;
        if ( _is_interrupted ) return kInterrupt;

        if ( event_queue_.size() > 0 ) {
            container = std::move(event_queue_.front());
            event_queue_.pop_front();
            return kGetEvent;
        }
        return kBroken;
    }

    void InsertNotifyOne(Item&& item) {
        std::lock_guard<std::mutex> _l(locker_);
        if ( !validate_ ) return;
        event_queue_.emplace_front(item);
        cv_.notify_one();
    }
    void NotifyOne(Item&& item) {
        std::lock_guard<std::mutex> _l(locker_);
        if ( !validate_ ) return;
        event_queue_.emplace_back(item);
        cv_.notify_one();
    }

    // Break specified waiting thread
    void BreakOne( breaker_t breaker = nullptr ) {
        std::lock_guard<std::mutex> _l(locker_);
        if ( !validate_ ) return;
        if ( breaker ) breaker();
        cv_.notify_all();
    }

    // break all waiting worker
    // once break, the pool will become invalidate and cannot be enabled again.
    void BreakAll() {
        std::lock_guard<std::mutex> _l(locker_);
        validate_ = false;
        cv_.notify_all();
    }

    // Re-enable
    void Enable() {
        std::lock_guard<std::mutex> _l(locker_);
        validate_ = true;
    }

    // Check if the pool is still available.
    bool IsValidate() const {
        std::lock_guard<std::mutex> _l(locker_);
        return validate_;
    }

    // Force to clear all items
    void Clear() {
        std::lock_guard<std::mutex> _l(locker_);
        while ( !event_queue_.empty() ) event_queue_.clear();
    }

    size_t PendingCount() const {
        std::lock_guard<std::mutex> _l(locker_);
        return event_queue_.size();
    }
protected:
    mutable std::mutex                  locker_;
    std::condition_variable             cv_;
    std::list<Item>                     event_queue_;
    bool                                validate_;
};

/**
 * @brief 等待信号管理
*/
template < typename LockType, LockType ValidateValue >
class PendingLockT {
public:
    bool Wait() {
        LockType _r;
        m_epl.Wait(_r);
        return _r == ValidateValue;
    }
    bool WaitUntil( typename EventQueue<LockType>::IntervalType d ) {
        LockType _r;
        auto _f = m_epl.WaitFor(d, _r);
        return (_f == EventQueue<LockType>::kGetEvent && _r == ValidateValue);
    }
    void JobDone() { m_epl.NotifyOne(ValidateValue); }

    PendingLockT() { m_epl.Enable(); }
    PendingLockT(const PendingLockT &) = delete;
    PendingLockT(PendingLockT&&) = delete;
    PendingLockT& operator= (const PendingLockT&) = delete;
    PendingLockT& operator= (PendingLockT&&) = delete;
protected:
    EventQueue<LockType> m_epl;
};

template < typename LockType, LockType ValidateValue >
class PendingLockKeeper {
public:
    typedef PendingLockT< LockType, ValidateValue >     lock_t;
    typedef std::shared_ptr< lock_t >                   ptr_lock_t;
public:
    PendingLockKeeper( ptr_lock_t pl ) : pl_(pl) { }
    PendingLockKeeper( const PendingLockKeeper& plk ) : pl_(plk.pl_) { plk.pl_ = nullptr; }
    PendingLockKeeper( PendingLockKeeper&& mplk ) : pl_(std::move(mplk.pl_)) { }
    ~PendingLockKeeper( ) { if ( pl_ != nullptr ) pl_->JobDone(); }
protected:
    mutable ptr_lock_t pl_;
};

typedef PendingLockT<bool, true> PendingLock;
typedef PendingLockKeeper<bool, true> PendingLockGuard;
typedef std::shared_ptr< PendingLock > SharedPendingLock;

#define CreatePendingLock(t)    bytertc::basic::SharedPendingLock t =   \
    std::make_shared< bytertc::basic::PendingLock >()

} // namespace basic
} // namespace bytertc

