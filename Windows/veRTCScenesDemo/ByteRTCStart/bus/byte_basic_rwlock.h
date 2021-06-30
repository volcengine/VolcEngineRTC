/*
 *  Copyright (c) 2020 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief read-write lock
 */

#include <iostream>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <atomic>

#pragma once

namespace bytertc {
namespace basic {

/**
 * @brief read write lock, and write first
*/
template < typename mutex_t = std::mutex >
class rw_lock_t {
public: 
    rw_lock_t() : read_cnt_(0), write_cnt_(0), is_writing_(false) { }
    ~rw_lock_t() { }

    /**
     * @brief Write Lock, increase the writer count, and wait all readers and other writers to quit
    */
    void lock() {
        std::unique_lock< std::mutex > _(mutex_);
        ++write_cnt_;
        while (read_cnt_ != 0 || is_writing_) {
            write_cond_.wait(_);
        }
        is_writing_ = true;
    }
    
    /**
     * @brief Try to write Lock, increase the writer count. If any other reader or writer, return false directly
    */
    bool try_lock() {
        std::unique_lock< std::mutex > _(mutex_);
        if (read_cnt_ != 0 || is_writing_) {
            return false;
        }
        ++write_cnt_;
        is_writing_ = true;
        return true;
    }
    
    /**
     * @brief Write Unlock, set is_writing to false, notify write or read
    */
    void unlock() {
        std::unique_lock< std::mutex > _(mutex_);
        if (write_cnt_ == 0) return;
        is_writing_ = false;
        if ((--write_cnt_) == 0) {
            read_cond_.notify_all();
        } else {
            write_cond_.notify_one();
        }
    }

    /**
     * @brief Read lock, wait until no writing, increase the reader count
    */
    void lock_shared() {
        std::unique_lock< std::mutex > _(mutex_);
        while (write_cnt_ != 0) {
            read_cond_.wait(_);
        }
        ++read_cnt_;
    }
    
    /**
     * @brief Read lock, wait until no writing, increase the reader count
    */
    bool try_lock_shared() {
        std::unique_lock< std::mutex > _(mutex_);
        if (write_cnt_ != 0) {
            return false;
        }
        ++read_cnt_;
        return true;
    }
    
    /**
     * @brief Read unlock, decrease reader count and notify the write thread.
    */
    void unlock_shared() {
        std::unique_lock< std::mutex > _(mutex_);
        if (read_cnt_ == 0) return;
        if ((--read_cnt_) == 0) {
            write_cond_.notify_one();
        };
    }
private:
    mutex_t mutex_;
    std::condition_variable read_cond_;
    std::condition_variable write_cond_;
    std::atomic<uint32_t> read_cnt_;
    std::atomic<uint32_t> write_cnt_;
    std::atomic<bool> is_writing_;
};
typedef rw_lock_t< std::mutex > rwlock;
}
}
