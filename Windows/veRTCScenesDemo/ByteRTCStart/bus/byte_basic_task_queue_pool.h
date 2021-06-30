/*
 *  Copyright (c) 2020 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief A Tool to manage multiple task queue
 */

#include "byte_basic_task_queue.h"

#pragma once
namespace bytertc {
namespace basic {

class TaskQueueManager {
public:
    typedef TaskQueue::Task_t               Task_t;
    typedef TaskQueue::IntervalType         IntervalType;
public:
    /**
     * @brief Enable taskmanager to get queue objects through taskqueue
    */
    void Initialize();

    /**
     * @brief Close taskmanager, no queue objects allowed
    */
    void Destroy();

    /**
     * @brief Create and maintain a task queue
     * @param name queue name
     * @return new queue id
    */
    uint64_t CreateQueue( const char* name = NULL );

    /**
     * @brief Destroy a queue by its id
    */
    void DestroyQueue( uint64_t qid );

    /**
     * @brief Close the entry channel without destroying any queues
    */
    void Shutdown();
    /**
     * @brief Wait until all backlog exits
     * @discuess This method implicitly calls destroy
    */
    void WaitUntilAllTaskDone( bool cancel_pending = false );

    /**
     * @brief Get statistics for all queues
    */
    std::map< std::string, TaskQueue::TraceResult > TraceInfo();

    /**
     * @brief Gets the available queue with the specified ID. if it does not exist, nullptr is returned
     * @note You need to determine the return value when calling this function
    */
    std::weak_ptr< TaskQueue > GetQueue( uint64_t qid );

    /**
     * @brief Structure and Deconstruction
    */
    TaskQueueManager();
    virtual ~TaskQueueManager();

private:
    std::mutex locker_;
    std::map< uint64_t, std::shared_ptr< TaskQueue > > qmap_;
    bool status_;
};

} // namespace basic
} // bytertc
 
