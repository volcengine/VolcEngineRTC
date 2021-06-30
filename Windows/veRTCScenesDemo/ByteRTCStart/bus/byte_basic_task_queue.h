/*
 *  Copyright (c) 2020 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief Task queue, thread model
 */


#pragma once

#include <atomic>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <type_traits>
#include <algorithm>

#include "byte_basic_location_type.h"
#include "byte_basic_weak_handler.h"
#include "byte_basic_event_queue.h"

namespace bytertc {
namespace basic {

/**
 * @brief Message queuing
*/
class TaskQueue : public std::enable_shared_from_this< TaskQueue >, public WeakHandler<TaskQueue> {
public:
    static constexpr uint64_t InvalidateQueueId = (uint64_t)-1;
    typedef std::chrono::nanoseconds                        IntervalType;
    typedef std::chrono::high_resolution_clock              HighResolutionTime;
    typedef std::chrono::time_point< HighResolutionTime >   Time_t;
    typedef std::function< void() >                         Task_t;

    typedef struct {
        int64_t              begin;
        int64_t              scheduled;
        int64_t              executed;
        TraceLocation       from;
    } TaskTraceInfo;

    typedef struct {
        uint32_t            begin_count;
        uint32_t            schedule_count;
        uint32_t            executed_count;
    } TaskTraceCounter;

    typedef struct {
        int64_t              total_time;
        int64_t              max_time;
        TaskTraceInfo       max_info;
        TaskTraceInfo       last_info;
    } TaskTraceTime;

    typedef struct {
        TaskTraceCounter    counter;
        TaskTraceTime       schedule_time;
        TaskTraceTime       execute_time;
    } TaskTraceResult;

    /**
     * @brief Statistics results，First is the increment from the last call to this call
     * Second is the sum of all data before the last call
    */
    typedef std::pair< TaskTraceResult, TaskTraceResult >   TraceResult;
    
    typedef std::pair< Task_t, TaskTraceInfo >              Task_Item;
    /**
     * @brief Task pool
    */
    typedef EventQueue< Task_Item >             TaskItemQueue;

    /**
     * @brief Delay task cache data structure
    */
    typedef struct {
        uint64_t                                task_id;
        Time_t                                  next_time;
        Task_t                                  task_job;
        TraceLocation                           task_from;
    } TimedTask;

public: 
    /**
     * @brief To create a new taskqueue, you need to specify the ID of the queue and the name displayed when debugging
     * If the ID is not specified, the address of this pointer is used as the qid by default
    */
    TaskQueue( uint64_t qid = InvalidateQueueId, const char* queue_name = NULL );

    virtual ~TaskQueue();

    /**
     * @brief The queue object is not allowed to be copied. If you need to pass the queue object，Please use shared_from_this
    */
    TaskQueue( const TaskQueue& ) = delete;
    TaskQueue( TaskQueue&& ) = delete;
    TaskQueue& operator= ( const TaskQueue& ) = delete;
    TaskQueue& operator= ( TaskQueue&& ) = delete;

    /**
     * @brief Initialize execution queue
    */
    void Startup();

    /**
     * @brief Initialize the execution queue and destroy the current queue.
     * After calling this method, new tasks will no longer be accepted，
     * All async / sync will be returned directly without affecting the processing of tasks already in the queue
    */
    void Shutdown();

    /**
     * @brief Check whether the current queue is running
    */
    bool Running() const;

    /**
     * @brief Wait until all backlog exits
     * @discuess This method implicitly calls destroy
    */
    void WaitUntilAllTaskDone( bool cancel_pending = false );

    /**
     * @brief Gets the ID of the current queue, and initializes it as the address of the queue object
    */
    uint64_t QueueId() const;

    /**
     * @brief If it is currently in the execution thread of a queue,
     * the ID of the current queue will be returned, otherwise -1
    */
    static uint64_t CurrentQueueId();

    /**
     * @brief whether the current executing thread is the thread of the queue
    */
    bool IsCurrent() const;
    
    /**
     * @brief If the Qid is not - 1, it is added to determine whether it is in a specific queue
     */
    static bool IsInQueue(uint64_t qid = InvalidateQueueId);

    /**
     * @brief Set the name of the current thread for debugging
    */
    void SetQueueName(const std::string& name);

    /**
     * @brief Get the name of the current queue
    */
    const std::string& QueueName() const;

    /**
     * @brief Switch the thread to the execution thread of the queue and execute the given task
    */
    void AsyncTask(TraceLocation&& from, Task_t handler);

    /**
     * @brief To execute a safe asynchronous task, you must pass in a safehandler, which is the this pointer
    */
    template < typename T >
    void SafeAsyncTask(TraceLocation&& from, WeakHandler<T>* pthis, Task_t handler) {
        this->AsyncTask(std::move(from), SafeWrapper(pthis, handler));
    }

    /**
     * @brief Switch thread to Queue execution thread and insert task into queue head execution
    */
    void EmergencyTask(TraceLocation&& from, Task_t handler);

    /**
     * @brief Safe asynchronous execution of urgent tasks must pass in a SafeHandler, which is the this pointer
    */
    template < typename T >
    void SafeEmergencyTask(TraceLocation&& from, WeakHandler<T>* pthis, Task_t handler) {
        this->EmergencyTask(std::move(from), SafeWrapper(pthis, handler));
    }
    
    /**
     * @brief Switch thread to Queue thread and wait for D to execute the given task
    */
    void AsyncDelayTask(TraceLocation&& from, IntervalType d, Task_t handler, 
            uint64_t task_id = (uint64_t)-1);

    /**
     * @brief Safe asynchronous execution of a deferred task must pass in a SafeHandler, which is the this pointer
    */
    template < typename T >
    void SafeAsyncDelayTask(TraceLocation&& from, IntervalType d, 
        WeakHandler<T>* pthis, Task_t handler, uint64_t task_id = (uint64_t)-1) {
        this->AsyncDelayTask(std::move(from), d, SafeWrapper(pthis, handler), task_id);
    }

    /**
     * @brief Cancel all time related tasks
    */
    void CancelDelayTask( uint64_t task_id );

    /**
     * @brief Execute tasks synchronously
     * @discuss Note, make sure you clearly understand what you are doing before calling this function，
     * Synchronization tasks implicitly extend the lifetime of locks, resources in the caller's function，
     * Make sure there are no deadlocks before calling
    */
    template < typename ReturnType >
    ReturnType SyncTask(TraceLocation&& from, std::function< ReturnType () > handler);

    /**
     * @brief Get a self-increasing task ID
    */
    static uint64_t NextTaskId();

    /**
     * @brief Get statistics for the current queue.In the returned pairs,
     * first is the incremental data from the last call to the current call,
     * and seconds is the total historical amount before the last call
    */
    TraceResult TraceInfo() const;
    
    /**
     * @brief Get queue_List, get its information for statistics and reporting
    */
    static std::map< uint64_t, WeakPtr< TaskQueue > > GetQueueList();
    
protected:
    /**
     * @brief Actual Scheduling Cycle
    */
    void Run();

    /**
     * @brief Stat api of task queue schedule
    */
    void __stat_clear(TaskTraceResult& result) const;
    void __stat_init();
    void __stat_post_task();
    void __stat_scheduled_task(TaskTraceInfo& tti);
    void __stat_executed_task(TaskTraceInfo& tti);
    void __stat_cut() const;

private:
    std::shared_ptr< std::mutex >                   running_lock_;
    // mutable std::mutex                              running_lock_;

    /**
     * @brief The status of the current queue, whether ready, if true, can accept a new task
    */
    mutable std::recursive_mutex                    ready_lock_;
    bool                                            queue_ready_;

    uint64_t                                        queue_id_;
    std::string                                     queue_name_;

    TaskItemQueue                                   task_queue_;
    std::recursive_mutex                            timed_lock_;
    std::list< TimedTask >                          timed_task_list_;

    mutable std::mutex                              trace_lock_;
    mutable TaskTraceResult                         trace_result_now_;
    mutable TaskTraceResult                         trace_result_history_;
};

/**
 * @brief Template Modeling Implementation of Synchronization Tasks
 * */
template < typename ReturnType > inline
ReturnType TaskQueue::SyncTask(TraceLocation&& from, std::function< ReturnType () > handler) {
    CreatePendingLock(_pl);
    PendingLockGuard _plg(_pl);
    ReturnType _ret;

    do {
        std::lock_guard< std::recursive_mutex > _(ready_lock_);
        if ( !queue_ready_ ) return _ret;

        if ( this->IsCurrent() ) return handler();
        this->AsyncTask(std::move(from), [_plg, handler, &_ret]() {
            _ret = handler();
        });
    } while ( false );

    _pl->Wait();
    return _ret;
}

/**
 * @brief Special implementation of synchronization task returning void
 */
template <>
void TaskQueue::SyncTask<void>(TraceLocation&& from, std::function< void () > handler);

/**
 * @brief Task Invoke Helper, make the task as an argument to the operator +=
*/
template < typename T >
class SafeTaskHelper {
public:
    SafeTaskHelper( std::weak_ptr< TaskQueue > q, WeakHandler<T>* p, TraceLocation&& f ) : 
        wq_(q), wp_(p), f_(std::move(f)) { }
    SafeTaskHelper( SafeTaskHelper&& h ) : 
        wq_(std::move(h.wq_)), wp_(std::move(h.wp_)), f_(std::move(h.f_)) { }
    SafeTaskHelper& operator << ( TaskQueue::Task_t task ) {
        if ( auto _sq = wq_.lock() ) {
            _sq->SafeAsyncTask(std::move(f_), wp_, task );
        }
        return *this;
    }

protected:
    std::weak_ptr< TaskQueue >      wq_;
    WeakHandler<T>*                 wp_;
    TraceLocation                   f_;
};
template < typename T > 
inline SafeTaskHelper<T> BuildSafeTaskHelper( std::weak_ptr< TaskQueue > q, WeakHandler<T>* p, TraceLocation&& f ) {
    return SafeTaskHelper<T>(q, p, std::move(f));
}

template < typename T >
class SafeDelayHelper {
public:
    SafeDelayHelper( std::weak_ptr< TaskQueue > q, WeakHandler<T>* p, TraceLocation&& f,
        TaskQueue::IntervalType d, uint64_t i = (uint64_t)-1) : 
        wq_(q), wp_(p), f_(std::move(f)), d_(d), i_(i) { }
    SafeDelayHelper( SafeDelayHelper&& h ) : 
        wq_(std::move(h.wq_)), wp_(std::move(h.wp_)), f_(std::move(h.f_)), d_(std::move(h.d_)), i_(h.i_) { }
    SafeDelayHelper& operator<< ( TaskQueue::Task_t task ) {
        if ( auto _sq = wq_.lock() ) {
            _sq->SafeAsyncDelayTask(std::move(f_), d_, wp_, task, i_);
        }
        return *this;
    }

protected:
    std::weak_ptr< TaskQueue >      wq_;
    WeakHandler<T>*                 wp_;
    TraceLocation                   f_;
    TaskQueue::IntervalType         d_;
    uint64_t                        i_;
};
template < typename T >
inline SafeDelayHelper<T> BuildSafeDelayHelper(
        std::weak_ptr< TaskQueue > q, WeakHandler<T>* p, TraceLocation&& f,
        TaskQueue::IntervalType d, uint64_t i = (uint64_t)-1) {
    return SafeDelayHelper<T>(q, p, std::move(f), d, i);
}

inline void CancelDelayHelper( std::weak_ptr< TaskQueue > wq, uint64_t tid ) {
    if ( auto _sq = wq.lock() ) {
        _sq->CancelDelayTask( tid );
    }
}
#define POST_TO_QUEUE(queue, weak_this)                \
    bytertc::basic::BuildSafeTaskHelper(queue, weak_this, CODE_FROM_HERE)

#define DELAY_ON_QUEUE(queue, weak_this, duration)     \
    bytertc::basic::BuildSafeDelayHelper(queue, weak_this, CODE_FROM_HERE, duration)

#define DELAY_ON_QUEUE_WITH_ID(queue, weak_this, duration, tid)    \
    bytertc::basic::BuildSafeDelayHelper(queue, weak_this, CODE_FROM_HERE, duration, tid)

#define CANCEL_ON_QUEUE(q, id)  bytertc::basic::CancelDelayHelper(q, id)

template < typename T >
class SyncHelper {
public:
    SyncHelper( std::weak_ptr< TaskQueue > q, TraceLocation&& f )
        : wq_(q), f_(std::move(f)) { }

    T operator << ( std::function< T() > task ) {
        if ( auto _sq = wq_.lock() ) {
            return _sq->template SyncTask<T>( std::move(f_), task );
        } else {
            return T();
        }
    }
protected:
    std::weak_ptr< TaskQueue >      wq_;
    TraceLocation                   f_;
};

#define SYNC_ON_QUEUE(queue, ret_type)                           \
    bytertc::basic::SyncHelper<ret_type>(queue, CODE_FROM_HERE)

/**
 * @brief Get the current time
*/
TaskQueue::Time_t TimeNow();
/**
 * @brief Gets the current UTC timestamp and the corresponding number of milliseconds
*/
int64_t TimeNowMs();

/**
 * @brief Convert time object to UTC timestamp(milliseconds)
*/
int64_t TimeToMs(const TaskQueue::Time_t& t);

} // namespace basicstd::decay<decltype(weak_this)>::type::HandlerType
} // naemspace bytertc
 
