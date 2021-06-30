/*
 *  Copyright (c) 2020 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief A Tool to manage multiple task queue
 */

#include "byte_basic_task_queue_pool.h"

namespace bytertc {
namespace basic {

TaskQueueManager::TaskQueueManager() : status_(false) { }
TaskQueueManager::~TaskQueueManager() {
    this->Destroy();
}

/**
 * @brief Start the taskqueue manager and allow to obtain the queue object through taskqueue
*/
void TaskQueueManager::Initialize() {
    std::lock_guard< std::mutex > _(locker_);
    status_ = true;
}

/**
 * @brief Stop taskqueuemanager, no queue objects allowed
*/
void TaskQueueManager::Destroy() {
    typedef std::map< uint64_t, std::shared_ptr< TaskQueue > >   __MQM_t;

    std::lock_guard< std::mutex > _(locker_);

    // If already destroied
    if ( status_ == false && 
         qmap_.size() == 0 ) return;

    // Set as closed
    status_ = false;

    for ( auto& mq : qmap_ ) {
        mq.second->Shutdown();
    }
    // Async Destroy all message queue object
    // it will not care which thread now is. just release everything.
    auto _c_map = std::make_shared< __MQM_t >( std::move(qmap_) );
    // Force Clear Again
    qmap_.clear();
    std::thread([_c_map]() {
        _c_map->clear();
    }).detach();
}

/**
 * @brief Create and maintain a task queue
 * @param name queue name
 * @return new queue id
*/
uint64_t TaskQueueManager::CreateQueue( const char* name ) {
    auto _queue = std::make_shared<TaskQueue>((uint64_t)-1, name);
    _queue->Startup();
    std::lock_guard< std::mutex > _(locker_);
    qmap_[_queue->QueueId()] = _queue;
    return _queue->QueueId();
}

/**
 * @brief Destroy a queue by its id
*/
void TaskQueueManager::DestroyQueue( uint64_t qid ) {
    std::lock_guard< std::mutex > _(locker_);
    auto _qit = qmap_.find(qid);
    if ( _qit == qmap_.end() ) return;

    auto _sq = _qit->second;
    _sq->Shutdown();
    qmap_.erase(_qit);

    // async delete the queue
    std::thread([_sq]() {
        _sq->WaitUntilAllTaskDone();
    }).detach();
}

/**
 * @brief Gets the available queue with the specified ID. if it has not been initialized or deleted, nullptr may be returned，
 * You need to determine the return value when calling this function
*/
std::weak_ptr< TaskQueue > TaskQueueManager::GetQueue( uint64_t qid ) {
    std::lock_guard< std::mutex > _(locker_);

    std::weak_ptr< TaskQueue > _wq;
    do {
        // if not initialize
        if ( !status_ ) break;

        auto _qit = qmap_.find( qid );
        // If find the queue
        if ( _qit != qmap_.end() ) {
            _wq = _qit->second;
        }
    } while ( false );
    return _wq;
}

/**
 * @brief Close the entry channel without destroying any queues
*/
void TaskQueueManager::Shutdown() {
    std::lock_guard< std::mutex > _(locker_);

    // If already destroied
    if ( status_ == false ) return;

    // Set as closed
    status_ = false;

    for ( auto& mq : qmap_ ) {
        mq.second->Shutdown();
    }
}
/**
 * @brief Wait until all backlog exits
 * @discuess When all backlog tasks exit, the method implicitly calls destroy
*/
void TaskQueueManager::WaitUntilAllTaskDone( bool cancel_pending ) {
    std::map< uint64_t, std::shared_ptr< TaskQueue > > _cached_map;
    do {
        std::lock_guard< std::mutex > _(locker_);
        _cached_map = qmap_;
    } while (false);
    for ( auto& mq : _cached_map ) {
        mq.second->WaitUntilAllTaskDone();
    }
}

/**
 * @brief Get statistics for all queues
*/
std::map< std::string, TaskQueue::TraceResult > TaskQueueManager::TraceInfo() {
    std::map< std::string, TaskQueue::TraceResult > _result;
    std::lock_guard< std::mutex > _(locker_);
    for ( auto& mq : qmap_ ) {
        _result[mq.second->QueueName()] = mq.second->TraceInfo();
    }
    return _result;
}

} // namespace basic
} // bytertc
 
