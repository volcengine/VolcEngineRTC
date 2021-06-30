/*
 *  Copyright (c) 2020 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief Secure message processor
 */

#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cassert>
#include <functional>
#include "byte_basic_rwlock.h"

#if defined(_MSC_VER) || defined(WIN32) || defined(WIN64)
#include <Windows.h>
#endif

#if defined(_MSC_VER) || defined(WIN32) || defined(WIN64)
#include <Windows.h>
#endif

#pragma once
namespace bytertc {
namespace basic {

/**
 * @brief Validate Pointer Wrapper
 * if the given mutex and flag is all right, then the ptr object
 * will hold the raw ptr, other wise, return a nullptr
*/
template < typename T >
class ValidatePtr {
public:
    typedef std::shared_ptr< rwlock >       MutexPtr;
    typedef std::shared_ptr< bool >         FlagPtr;
public: 

    /**
     * @brief Create the validate ptr with mutex, flag and raw ptr
    */
    ValidatePtr<T>( MutexPtr m, FlagPtr f, T* ptr ) : 
        lock_(m) {
        if ( lock_ ) lock_->lock_shared();
        if ( f ) {
            raw_ptr_ = (*f ? ptr : nullptr);
        } else {
            raw_ptr_ = nullptr;
        }
    }
    /**
     * @brief support move operator, the old ptr will be nullptr
    */
    ValidatePtr<T>( ValidatePtr<T>&& vp ) : 
        lock_( std::move(vp.lock_) ), raw_ptr_(vp.raw_ptr_) {
        // Force old vp to be null
        vp.raw_ptr_ = nullptr;
    }
    ValidatePtr<T>& operator = ( ValidatePtr<T>&& vp ) {
        if ( this == &vp ) return *this;
        lock_ = std::move(vp.lock_);
        raw_ptr_ = std::move(vp.raw_ptr_);
        vp.raw_ptr_ = nullptr;
        return *this;
    }
    ~ValidatePtr<T>() { if ( lock_ ) { lock_->unlock_shared(); } }
    
    T* Get() { return raw_ptr_; }
    /**
     * @brief Check if current ptr is validate
    */
    operator bool() const { return raw_ptr_ != nullptr; }
    /**
     * @brief Smart ptr operator override
    */
    T* operator ->() { return raw_ptr_; }
    T& operator *() { return *raw_ptr_; }
private:
    MutexPtr                    lock_;
    T*                          raw_ptr_;
};

/**
 * @brief Sample Weak Pointer, Used to make sure the original ptr is still available
*/
template < typename T >
class WeakPtr {
public:
    typedef std::shared_ptr< rwlock >       MutexPtr;
    typedef std::shared_ptr< bool >         FlagPtr;

public:
    /**
     * @brief Support all type constructors, except from raw ptr
    */
    WeakPtr( ) : lock_(nullptr), flag_(nullptr), raw_ptr_(nullptr) { }
    WeakPtr( MutexPtr lock, FlagPtr flag, T* ptr ) : 
        lock_(lock), flag_(flag), raw_ptr_(ptr) { }
    WeakPtr( const WeakPtr& wp ) : lock_(wp.lock_), flag_(wp.flag_), raw_ptr_(wp.raw_ptr_) { }
    WeakPtr( WeakPtr&& wp ) : 
        lock_( std::move(wp.lock_) ),
        flag_( std::move(wp.flag_) ),
        raw_ptr_( std::move(wp.raw_ptr_) ) {
    }
    WeakPtr& operator = ( const WeakPtr& wp ) {
        if ( this == &wp ) return *this;
        lock_ = wp.lock_;
        flag_ = wp.flag_;
        raw_ptr_ = wp.raw_ptr_;
        return *this;
    }
    WeakPtr& operator = ( WeakPtr&& wp ) {
        if ( this == &wp ) return *this;
        lock_ = std::move( wp.lock_ ); wp.lock_ = nullptr;
        flag_ = std::move( wp.flag_ ); wp.flag_ = nullptr;
        raw_ptr_ = std::move( wp.raw_ptr_ ); wp.raw_ptr_ = nullptr;
        return *this;
    }

    /**
     * @brief Lock current ptr object, and get a validate ptr.
     * If the raw ptr is still available, the validate ptr will lock and be validate
     * other wise, the validate ptr will be null
     * @usage
     *  if ( auto _vp = wp.Lock() ) {
     *      _vp->doFoo();
     *  }
    */
    ValidatePtr< T > Lock() const { return ValidatePtr<T>( lock_, flag_, raw_ptr_ ); }
private:
    MutexPtr                    lock_;
    FlagPtr                     flag_;
    T*                          raw_ptr_;
};

/**
 * @brief Weak Handler Base Class
 * @usage
 * class MyHandler : public WeakHandler<MyHandler> {
 * public:
 *      void Foo() {
 *          auto _weak_this = this->WeakThis();
 *          std::async([_weak_this]() {
 *              if ( auto _strong_this = _weak_this.Lock() ) {
 *                  // do something
 *              }
 *          });
 *      } 
 * };
*/
template < typename T > 
class WeakHandler {
public:
    typedef std::shared_ptr< rwlock >       MutexPtr;
    typedef std::shared_ptr< bool >         FlagPtr;
public:
    WeakHandler() : 
        lock_(std::make_shared< rwlock >()),
        flag_(std::make_shared<bool>(true)), 
        raw_ptr_(static_cast<T*>(this)) { }

    virtual ~WeakHandler() {
        this->SafeDestroy();
    }

    /**
     * @brief Manually invoke this if destroy an object in different thread
    */
    void SafeDestroy() {
        std::unique_lock< rwlock >  _(*lock_);
        *flag_ = false;
        raw_ptr_ = nullptr;
    }

    /**
     * @brief Create a weak ptr from current this point.
    */
    WeakPtr<T> WeakThis() { 
        return WeakPtr<T>(lock_, flag_, raw_ptr_); 
    }

private:
    MutexPtr                    lock_;
    FlagPtr                     flag_;
    T*                          raw_ptr_;
};

/**
 * @brief Safe Lambda Wrapper, the handler can capture `this`
*/
template < typename T >
std::function<void()> SafeWrapper( WeakHandler<T>* weak_this, std::function< void() > handler ) {
    if ( weak_this == NULL || !handler ) return nullptr;
    auto _wthis = weak_this->WeakThis();
    return std::function< void () >([_wthis, handler]() {
        if ( auto _vp = _wthis.Lock() ) {
            handler();
        }
    });
}

/**
 * @brief C language Atomic operation，CAS，Avoid using STL encapsulation，Can be used in static variables
*/
inline bool CompareAndSwap( volatile int32_t* address, int32_t except_value, int32_t new_value ) {
    #if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
    return __atomic_compare_exchange_n(address, &except_value, new_value, false, __ATOMIC_SEQ_CST, __ATOMIC_ACQUIRE);
    #elif defined(_MSC_VER)
    return (except_value == InterlockedCompareExchange(
        (volatile unsigned int *)address, (unsigned int)new_value, (unsigned int)except_value));
    #else
    #error Unsupport compiler
    #endif
}

/**
 * @brief Spin lock, internal use CAS implementation, do not use STL method, can be used safely in static variables
*/
class SpinLock {
public:
    bool try_lock() {
        return CompareAndSwap(&status_, 0, 1);
    }
    void lock() {
        uint16_t counter = 0;
        while ( !CompareAndSwap(&status_, 0, 1) ) {
            ++counter;
            if ( counter == 4000 ) {
                counter = 0;
                std::this_thread::yield();
            }
        }
    }
    void unlock() {
        status_ = 0;
    }
protected:
    volatile int32_t status_ = 0;
};

/**
 * @briefStatic variable container can protect static variables more safely,
 * so as to prevent asynchronous thread from delaying destruction when the program exits,
 * resulting in wrong access to released static variables
*/
template < typename ItemType >
class StaticWrapper {
public:
    // Default
    StaticWrapper() {}
    ~StaticWrapper() {
        std::lock_guard<SpinLock> _(locker_);
        destroied_ = true;
    }
    WeakPtr<ItemType> SafeGet() {
        WeakPtr<ItemType> wptr;
        std::lock_guard<SpinLock> _(locker_);
        if ( !destroied_ ) {
            wptr = weak_item_.WeakThis();
        }
        return wptr;
    }
protected:
    volatile bool               destroied_ = false;
    SpinLock                    locker_;
    ItemType                    weak_item_;
};

/**
 * @brief Convert any object that is not a weakhandler to a weakhandler
*/
template < typename ItemType >
class WeakWrapper : public WeakHandler< WeakWrapper<ItemType> > {
public:
    ItemType& GetItem() { return item_; }
protected:
    ItemType    item_;
};

} // namespace basic
} // namespace bytertc
 
