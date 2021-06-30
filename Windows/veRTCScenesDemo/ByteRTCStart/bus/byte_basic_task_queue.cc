/*
 *  Copyright (c) 2020 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief Task Queue, Thread Model
 */

#include "byte_basic_task_queue.h"
#include <assert.h>
#ifdef WIN32
#include <windows.h>
#elif defined(__linux__) || defined(__ANDROID__)
#include <sys/prctl.h>
#endif
#include <cstring>

namespace {
void __byte_mq_set_current_thread_name(const char* name) {
#if defined(WIN32)
    struct {
        DWORD dwType;
        LPCSTR szName;
        DWORD dwThreadID;
        DWORD dwFlags;
    } threadname_info = {0x1000, name, static_cast<DWORD>(-1), 0};

    __try {
        ::RaiseException(
                0x406D1388, 0, sizeof(threadname_info) / sizeof(DWORD), 
                reinterpret_cast<ULONG_PTR*>(&threadname_info));
    } __except (EXCEPTION_EXECUTE_HANDLER) {  // NOLINT
    }
#elif defined(__linux__) || defined(__ANDROID__)
    prctl(PR_SET_NAME, reinterpret_cast<unsigned long>(name));  // NOLINT
#elif defined(__APPLE__)
    pthread_setname_np(name);
#endif
}
} // namespace

#if defined(__APPLE__)
/*
 * These are forward-declarations for methods that are part of the
 * ObjC runtime. They are declared in the private header objc-internal.h.
 * These calls are what clang inserts when using @autoreleasepool in ObjC,
 * but here they are used directly in order to keep this file C++.
 * https://clang.llvm.org/docs/AutomaticReferenceCounting.html#runtime-support
 */
extern "C" {
void* objc_autoreleasePoolPush(void);
void objc_autoreleasePoolPop(void* pool);
}

namespace {
class ScopedAutoReleasePool {
public:
    ScopedAutoReleasePool() : pool_(objc_autoreleasePoolPush()) {}
    ~ScopedAutoReleasePool() { objc_autoreleasePoolPop(pool_); }

private:
    void* const pool_;
};
}  // namespace

#define TASK_QUEUE_ENABLE_AUTORELEASE_POOL      ScopedAutoReleasePool __pool__;
#else
#define TASK_QUEUE_ENABLE_AUTORELEASE_POOL
#endif

namespace bytertc {
namespace basic {

/**
 * @brief Get the current time
*/
TaskQueue::Time_t TimeNow() {
    return std::chrono::high_resolution_clock::now();
}

/**
 * @brief Gets the current UTC timestamp and the corresponding number of milliseconds
*/
int64_t TimeNowMs() {
    return (int64_t) std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();
}

/**
 * @brief Converting a time object to a UTC timestamp (milliseconds)
*/
int64_t TimeToMs(const TaskQueue::Time_t& t) {
    return (int64_t) std::chrono::duration_cast<std::chrono::milliseconds>
        (t.time_since_epoch()).count();
}

// Xcode Support `thread_local` after 8.0, and iOS not support `thread_local` earlier than 9.0
namespace TaskQueueGlobalInfo {
typedef WeakWrapper< std::mutex >                           WeakableMutex;
typedef WeakWrapper< std::map<std::thread::id, uint64_t> >  WeakableIdMap;

WeakPtr< WeakableMutex > CurrentQueueIdLock() {
    static StaticWrapper< WeakableMutex > s_current_qid_lock;
    return s_current_qid_lock.SafeGet();
}
WeakPtr< WeakableIdMap > CurrentQueueIdMap() {
    static StaticWrapper< WeakableIdMap > s_current_qid_map;
    return s_current_qid_map.SafeGet();
}
}

// thread_local static uint32_t g_current_qid = (uint32_t)-1;
uint64_t thread_get_current_qid() {
    auto weak_id_lock = TaskQueueGlobalInfo::CurrentQueueIdLock();
    if ( auto strong_id_lock = weak_id_lock.Lock() ) {
        std::lock_guard< std::mutex > _(strong_id_lock->GetItem());
        auto weak_id_map = TaskQueueGlobalInfo::CurrentQueueIdMap();
        if ( auto strong_id_map = weak_id_map.Lock() ) {
            auto _qit = strong_id_map->GetItem().find(std::this_thread::get_id());
            if ( _qit == strong_id_map->GetItem().end() ) {
                return TaskQueue::InvalidateQueueId;
            }
            return _qit->second;
        } else {
            return TaskQueue::InvalidateQueueId;
        }
    } else {
        return TaskQueue::InvalidateQueueId;
    }
}
void thread_set_current_qid(uint64_t qid) {
    auto weak_id_lock = TaskQueueGlobalInfo::CurrentQueueIdLock();
    if ( auto strong_id_lock = weak_id_lock.Lock() ) {
        std::lock_guard< std::mutex > _(strong_id_lock->GetItem());
        auto weak_id_map = TaskQueueGlobalInfo::CurrentQueueIdMap();
        if ( auto strong_id_map = weak_id_map.Lock() ) {
            if ( qid == TaskQueue::InvalidateQueueId ) {
                strong_id_map->GetItem().erase(std::this_thread::get_id());
            } else {
                strong_id_map->GetItem()[std::this_thread::get_id()] = qid;
            }
        }
    }
}

namespace TaskQueueList {
std::mutex& Locker() {
    static std::mutex locker_;
    return locker_;
}
std::map< uint64_t, WeakPtr< TaskQueue > >& QueueMap() {
    static std::map< uint64_t, WeakPtr< TaskQueue > > queue_map_;
    return queue_map_;
}
void AddQueue(uint64_t qid, WeakPtr<TaskQueue> q) {
    std::lock_guard< std::mutex > _(Locker());
    QueueMap()[qid] = q;
}
void DeleteQueue(uint64_t qid) {
    std::lock_guard< std::mutex > _(Locker());
    QueueMap().erase(qid);
}
} // namespace TaskQueueList

std::map< uint64_t, WeakPtr< TaskQueue > > TaskQueue::GetQueueList(){
    std::lock_guard< std::mutex > _(TaskQueueList::Locker());
    return TaskQueueList::QueueMap();
}

TaskQueue::TaskQueue(uint64_t qid, const char* queue_name)
    : 
    running_lock_(std::make_shared<std::mutex>()),
    queue_ready_(false),
    queue_id_(qid) {

    // Use this address as the id of queue
    if ( queue_id_ == TaskQueue::InvalidateQueueId ) {
        queue_id_ = static_cast<uint64_t>((intptr_t)this);
    }
    if ( queue_name != NULL ) {
        queue_name_ = queue_name;
    } else {
        queue_name_ = "TaskQueue " + std::to_string(qid);
    }
}
TaskQueue::~TaskQueue() {
    this->WaitUntilAllTaskDone();
}

void TaskQueue::Startup() {
    std::lock_guard< std::recursive_mutex > _(ready_lock_);
    if ( queue_ready_ ) return;
    queue_ready_ = true;

    // Make sure last destroy has already finished
    // this->running_lock_.lock();
    CreatePendingLock(_spl);
    std::weak_ptr< PendingLock > _wpl = _spl;
    std::shared_ptr< std::mutex > _srlock = running_lock_;
    std::thread _runner([this, _wpl, _srlock]() {
        ::__byte_mq_set_current_thread_name(this->queue_name_.c_str());
        thread_set_current_qid(this->queue_id_);

        std::lock_guard< std::mutex > _(*_srlock);
        
        TaskQueueList::AddQueue(this->queue_id_, this->WeakThis());
        
        // Init trace info
        this->__stat_init();
        // Start the task queue
        task_queue_.Enable();
        // Give signal to the start thread
        if ( auto _s = _wpl.lock() ) {
            _s->JobDone();
        }
        // Begin RunLoop
        this->Run();

        TaskQueueList::DeleteQueue(this->queue_id_);
        thread_set_current_qid(TaskQueue::InvalidateQueueId);
    });

    // wait for the runner begun
    _spl->Wait();
    _runner.detach();
}

/**
 * @brief Destroy the current queue. After calling this method,
 * new tasks will not be accepted and all async/syncs will return directly,
 * without affecting the processing of tasks already in the queue
*/
void TaskQueue::Shutdown() {
    std::lock_guard< std::recursive_mutex > _(ready_lock_);
    // Already destroied
    if ( queue_ready_ == false ) return;
    queue_ready_ = false;

    do {
        /**
         * Force clearance of all backlogged sequential tasks
        */
        std::lock_guard< std::recursive_mutex > _2(timed_lock_);
        timed_task_list_.clear();
    } while ( false );
    /**
     * Mark EventQueue as Invalidate to force the Run thread to exit and safely release itself
    */
    task_queue_.BreakAll();
}

/**
 * @brief Check to see if the current Queue is running
*/
bool TaskQueue::Running() const {
    if ( ! running_lock_->try_lock() ) return true;
    running_lock_->unlock();
    return false;
}

/**
 * @brief Wait until all backlogged tasks exit
*/
void TaskQueue::WaitUntilAllTaskDone( bool cancel_pending ) {
    this->Shutdown();
    if ( cancel_pending || this->IsCurrent() ) {
        task_queue_.Clear();
    }
    // Wait for all task done
    if ( !this->IsCurrent() ) {
        std::lock_guard< std::mutex > _(*this->running_lock_);
    }
}

/**
 * @brief Gets the ID of the current Queue and initializes it to the address of the Queue object
*/
uint64_t TaskQueue::QueueId() const { return queue_id_; }

/**
 * @brief Returns the ID of the current Queue if it is currently in the execution thread of a Queue, otherwise -1
*/
uint64_t TaskQueue::CurrentQueueId() { return thread_get_current_qid(); }

/**
 * @brief Determine if the current execution thread is the same as queue
*/
bool TaskQueue::IsCurrent() const { return IsInQueue( queue_id_ ); }

/**
 * @brief Whether currently in Queue, if Qid is not -1, append to determine if in a particular Queue
 */
bool TaskQueue::IsInQueue(uint64_t qid) {
    uint64_t _cqid = thread_get_current_qid();
    bool _is_inqueue = ( _cqid != TaskQueue::InvalidateQueueId );
    if ( !_is_inqueue ) return false;
    return ( (qid == TaskQueue::InvalidateQueueId) ? true : (_cqid == qid) );
}

/**
 * @brief Set the name of the current execution thread for debugging purposes
*/
void TaskQueue::SetQueueName( const std::string& name ) {
    queue_name_ = name;
    this->AsyncTask(CODE_FROM_HERE, [name]() {
        ::__byte_mq_set_current_thread_name(name.c_str());
    });
}
/**
 * @brief Get the name of the current queue
*/
const std::string& TaskQueue::QueueName() const { return queue_name_; }

/**
 * @brief Asynchronous execution of a single task randomly generates an anonymous event
*/
void TaskQueue::AsyncTask(TraceLocation&& from, Task_t handler) {
    if ( handler == nullptr ) return;

    std::lock_guard< std::recursive_mutex > _(ready_lock_);
    if ( !queue_ready_ ) return;

    // Just insert the task
    TaskTraceInfo _tti{TimeNowMs(), 0, 0, std::move(from)};
    __stat_post_task();
    task_queue_.NotifyOne(std::make_pair(std::move(handler), std::move(_tti)));
}

/**
 * @brief Switch thread to Queue execution thread and insert task into queue head execution
*/
void TaskQueue::EmergencyTask(TraceLocation&& from, Task_t handler) {
    if ( handler == nullptr ) return;

    std::lock_guard< std::recursive_mutex > _(ready_lock_);
    if ( !queue_ready_ ) return;

    // Just insert the task
    TaskTraceInfo _tti{TimeNowMs(), 0, 0, std::move(from)};
    __stat_post_task();
    task_queue_.InsertNotifyOne(std::make_pair(std::move(handler), std::move(_tti)));
}

/**
 * @brief Switch thread to Queue thread and wait for D to execute the given task
*/
void TaskQueue::AsyncDelayTask(TraceLocation&& from, IntervalType d, Task_t handler, uint64_t task_id) {
    if ( handler == nullptr ) return;

    std::lock_guard< std::recursive_mutex > _(ready_lock_);
    if ( !queue_ready_ ) return;

    Time_t _now = TimeNow();
    TaskQueue::TimedTask _tm{task_id, _now + d, handler, std::move(from)};

    task_queue_.BreakOne([&]() {
        std::lock_guard< std::recursive_mutex > _tl(timed_lock_);
        timed_task_list_.insert(
            std::lower_bound(
                timed_task_list_.begin(), 
                timed_task_list_.end(), 
                _tm, 
                [](const TaskQueue::TimedTask& _1, const TaskQueue::TimedTask& _2) -> bool {
                    return _1.next_time < _2.next_time;
                }
            ), _tm
        );
    });
}


/**
 * @brief Cancel all time related tasks
*/
void TaskQueue::CancelDelayTask( uint64_t task_id ) {
    task_queue_.BreakOne([&]() {
        std::lock_guard< std::recursive_mutex > _(timed_lock_);
        if ( task_id == (uint64_t)-1 ) {
            timed_task_list_.clear(); return;
        }
        auto _itm = std::find_if(timed_task_list_.begin(), timed_task_list_.end(),
            [task_id](const TaskQueue::TimedTask& tm ) -> bool {
                return tm.task_id == task_id;
            }
        );
        if ( _itm != timed_task_list_.end() ) {
            timed_task_list_.erase(_itm);
        }
    });
}

/**
 * @brief Special implementation of synchronization task returning void
 */
template <>
void TaskQueue::SyncTask<void>(TraceLocation&& from, std::function< void() > handler) {

    CreatePendingLock(_pl);
    PendingLockGuard _plg(_pl);
    do {
    	std::lock_guard< std::recursive_mutex > _(ready_lock_);
       	if ( !queue_ready_ ) return;

       	if ( this->IsCurrent() ) return handler();
        this->AsyncTask(std::move(from), [_plg, handler]() {
        	handler();
        });
    } while ( false );

    _pl->Wait();
}
/**
 * @brief Get a self-increasing task ID
*/
uint64_t TaskQueue::NextTaskId() {
    static std::atomic<uint64_t> g_tid(0);
    return g_tid++;
}

void TaskQueue::Run() {
    Task_Item _task;
    auto _wthis = this->WeakThis();
    do {
        /**
         * Default wait time of 1 second
        */
        IntervalType _gap = std::chrono::milliseconds(1000);
        /**
         * Calculate the timed msg gap
        */
        std::size_t _dmsg_size = 0;
        do {
            //std::lock_guard< std::recursive_mutex > _(timed_lock_);
            timed_lock_.lock();
            /**
             * No timed message
            */
            _dmsg_size = timed_task_list_.size();
            if ( timed_task_list_.size() == 0 ) {
                timed_lock_.unlock();
                break;
            }
            Time_t _now = TimeNow();
            Time_t _run_time = timed_task_list_.begin()->next_time;
            /**
             * Need to run now
            */
            if ( _run_time <= _now ) {
                /**
                 * fetch top one
                */
                auto _tm = *timed_task_list_.begin();
                timed_task_list_.pop_front();
                _dmsg_size -= 1;
                timed_lock_.unlock();
                /**
                 * Insert into the begin of the task queue
                */
                TaskTraceInfo _tti{TimeNowMs(), 0, 0, std::move(_tm.task_from)};
                __stat_post_task();
                this->task_queue_.InsertNotifyOne(
                    std::make_pair(std::move(_tm.task_job), std::move(_tti)));
            } else {
                _gap = (_run_time - _now);
                timed_lock_.unlock();
            }
        } while ( false );
        /**
         * if gap <= 0, insertNotify, otherwise, use the gap as timeout
        */

        auto _f = task_queue_.WaitFor(_gap, _task, [this, _dmsg_size]() -> bool {
            std::lock_guard< std::recursive_mutex > _(timed_lock_);
            return _dmsg_size != this->timed_task_list_.size();
        });
        /**
         * Exit the current loop when a break or timeout is received
        */
        if ( _f == TaskQueue::TaskItemQueue::kBroken ) break;
        /**
         * Timeout without new task
        */
        if ( _f == TaskQueue::TaskItemQueue::kNoEvent ) continue;
        /**
         * Delayed task insertion, forced to interrupt current wait, recalculate gap
        */
        if ( _f == TaskQueue::TaskItemQueue::kInterrupt ) continue;

        /**
         * did get a pending task, invoke it
        */
        __stat_scheduled_task(_task.second);
        if ( _task.first ) {
            TASK_QUEUE_ENABLE_AUTORELEASE_POOL
            _task.first();
            _task.first = nullptr;
            if ( auto _vthis = _wthis.Lock() ) {
                __stat_executed_task(_task.second);
            } else {
                // Already delete this, no need to do anything, just return
                return;
            }
        }
    } while ( true );

    do {
        std::lock_guard< std::recursive_mutex > _(timed_lock_);
        timed_task_list_.clear();
    } while ( false );
}

/**
 * @brief Stat api of task queue schedule
*/
void TaskQueue::__stat_clear(TaskTraceResult& result) const {
    memset(&result.counter, 0, sizeof(TaskTraceCounter));
    result.schedule_time.total_time = 0;
    result.schedule_time.max_time = 0;
    result.schedule_time.max_info.begin = 0;
    result.schedule_time.max_info.scheduled = 0;
    result.schedule_time.max_info.executed = 0;
    result.schedule_time.max_info.from.clear();
    result.schedule_time.last_info.begin = 0;
    result.schedule_time.last_info.scheduled = 0;
    result.schedule_time.last_info.executed = 0;
    result.schedule_time.last_info.from.clear();
    result.execute_time.total_time = 0;
    result.execute_time.max_time = 0;
    result.execute_time.max_info.begin = 0;
    result.execute_time.max_info.scheduled = 0;
    result.execute_time.max_info.executed = 0;
    result.execute_time.max_info.from.clear();
    result.execute_time.last_info.begin = 0;
    result.execute_time.last_info.scheduled = 0;
    result.execute_time.last_info.executed = 0;
    result.execute_time.last_info.from.clear();
}
void TaskQueue::__stat_init() {
    std::lock_guard< std::mutex > _(trace_lock_);
    __stat_clear(trace_result_now_);
    __stat_clear(trace_result_history_);
}
void TaskQueue::__stat_post_task() {
    std::lock_guard< std::mutex > _(trace_lock_);
    trace_result_now_.counter.begin_count += 1;
}
void TaskQueue::__stat_scheduled_task(TaskTraceInfo& tti) {
    std::lock_guard< std::mutex > _(trace_lock_);
    trace_result_now_.counter.schedule_count += 1;
    tti.scheduled = TimeNowMs();
    int64_t _s_time = tti.scheduled - tti.begin;
    trace_result_now_.schedule_time.total_time += _s_time;
    if ( _s_time > trace_result_now_.schedule_time.max_time ) {
        trace_result_now_.schedule_time.max_time = _s_time;
        trace_result_now_.schedule_time.max_info = tti;
    }
    trace_result_now_.schedule_time.last_info = tti;
}
void TaskQueue::__stat_executed_task(TaskTraceInfo& tti) {
    std::lock_guard< std::mutex > _(trace_lock_);
    trace_result_now_.counter.executed_count += 1;
    tti.executed = TimeNowMs();
    int64_t _e_time = tti.executed - tti.scheduled;
    trace_result_now_.execute_time.total_time += _e_time;
    if ( _e_time > trace_result_now_.execute_time.max_time ) {
        trace_result_now_.execute_time.max_time = _e_time;
        trace_result_now_.execute_time.max_info = tti;
    }
    trace_result_now_.execute_time.last_info = tti;
}
void TaskQueue::__stat_cut() const {
    trace_result_history_.counter.begin_count += trace_result_now_.counter.begin_count;
    trace_result_history_.counter.schedule_count += trace_result_now_.counter.schedule_count;
    trace_result_history_.counter.executed_count += trace_result_now_.counter.executed_count;
    trace_result_history_.schedule_time.total_time += trace_result_now_.schedule_time.total_time;
    trace_result_history_.execute_time.total_time += trace_result_now_.execute_time.total_time;
    __stat_clear(trace_result_now_);
}
/**
 * @brief Gets statistics for the current queue,
 * returns pairs with first as incremental data from the last call to the current call
 * and seconds as total historical data before the last call
*/
TaskQueue::TraceResult TaskQueue::TraceInfo() const {
    std::lock_guard< std::mutex > _(trace_lock_);
    TaskQueue::TraceResult _r = std::make_pair(trace_result_now_, trace_result_history_);
    this->__stat_cut();
    return _r;
}

} // namespace basic
} // namespace bytertc
 
