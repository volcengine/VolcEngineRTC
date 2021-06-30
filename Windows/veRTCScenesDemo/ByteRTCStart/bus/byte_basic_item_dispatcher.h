/*
 *  Copyright (c) 2020 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief Object distributor
 */

#pragma once 

#include <iostream>
#include <mutex>
#include <unordered_map>
#include <list>
#include <string>
#include <memory>

namespace bytertc {
namespace basic {

/**
 * @brief A simple item dispatcher, receive from one side and dispatch to 
 * multiple subscribers
*/
template < typename Item, typename ItemKey > 
class ItemDispatcher {
public: 
    /**
     * @brief Subscriber Handler Function
    */
    typedef std::function< void (Item&) >       SubscriberFunc;
    typedef struct {
        std::string             subkey;
        SubscriberFunc          subscriber;
        bool                    is_oneshot;
    } ItemSubscriberInfo;

    typedef std::list< ItemSubscriberInfo >                 SubscriberList;
    typedef std::unordered_map< ItemKey, SubscriberList >   SubscriberMap;

public:

    /**
     * @brief Default Constructor, the status is false, means the dispatcher is been closed.
    */
    ItemDispatcher() : status_(false) { }

    /**
     * @brief Safe Copy
    */
    ItemDispatcher( const ItemDispatcher& d ) { *this = d; }
    ItemDispatcher& operator = ( const ItemDispatcher& d ) {
        if ( this == &d ) return *this;
        std::unique_lock< std::mutex > _sll(status_lock_, std::defer_lock);
        std::unique_lock< std::mutex > _dll(dispatcher_lock_, std::defer_lock);
        std::unique_lock< std::mutex > _sl(d.status_lock_, std::defer_lock);
        std::unique_lock< std::mutex > _dl(d.dispatcher_lock_, std::defer_lock);
        std::lock( _sll, _dll, _sl, _dl );
        status_ = d.status_;
        sub_map_ = d.sub_map_;
        return *this;
    }
    /**
     * @brief Safe Move
    */
    ItemDispatcher( ItemDispatcher&& d ) { *this = std::move(d); }
    ItemDispatcher& operator = ( ItemDispatcher&& d ) {
        if ( this == &d ) return *this;
        std::unique_lock< std::mutex > _sll(status_lock_, std::defer_lock);
        std::unique_lock< std::mutex > _dll(dispatcher_lock_, std::defer_lock);
        std::unique_lock< std::mutex > _sl(d.status_lock_, std::defer_lock);
        std::unique_lock< std::mutex > _dl(d.dispatcher_lock_, std::defer_lock);
        std::lock( _sll, _dll, _sl, _dl );
        status_ = std::move(d.status_);
        d.status_ = false;
        sub_map_ = std::move(d.sub_map_);
        return *this;
    }


    /**
     * @brief Open or close the dispatcher
    */
    void Enable( bool enable ) {
        std::lock_guard< std::mutex > _(status_lock_);
        status_ = enable;
    }

    /**
     * @brief Check if the dispatcher is enabled.
    */
    bool IsEnabled() const {
        std::lock_guard< std::mutex > _(status_lock_);
        return status_;
    }

    /**
     * @brief Publish an item with key to the dispatcher
     * and search for the subscriber to handle it.
     * @discuss if the dispatcher is closed, the function will return and do nothing
    */
    void Publish( ItemKey key, Item& item ) {
        std::list< SubscriberFunc > _lsf;

        do {
            // Lock all
            std::unique_lock< std::mutex > _sl(status_lock_, std::defer_lock);
            std::unique_lock< std::mutex > _dl(dispatcher_lock_, std::defer_lock);
            std::lock( _sl, _dl );

            // Not Start, Dispatcher Closed
            if ( !status_ ) break;

            // Find the subscriber list
            auto _s = sub_map_.find( key );
            // No subscriber for current item
            if ( _s == sub_map_.end() ) break;

            // Check if is oneshot or nullptr
            for ( auto _sit = _s->second.begin(); _sit != _s->second.end(); /* void */ ) {
                _lsf.push_back(_sit->subscriber);
                if ( _sit->is_oneshot || (_sit->subscriber == nullptr) ) {
                    _sit = _s->second.erase(_sit);
                } else {
                    ++_sit;
                }
            }
        } while ( false );

        for ( auto& s : _lsf ) {
            if ( s == nullptr ) continue;
            s(item);
        }
    }

    /**
     * @brief Register a subscriber to specified item
     * if the input func is nullptr, means delete the registered subscriber
    */
    void Subscribe( ItemKey key, SubscriberFunc func, bool is_oneshot, const std::string& subkey ) {
        std::lock_guard< std::mutex > _(dispatcher_lock_);
        auto _sit = sub_map_.find( key );
        // no subscriber on same item
        if ( _sit == sub_map_.end() ) {
            // no need to remove 
            if ( func == nullptr ) return;
            // create new list
            _sit = sub_map_.emplace( std::make_pair( key, SubscriberList{}) ).first;
            // add to tail
            _sit->second.emplace_back( ItemSubscriberInfo{subkey, func, is_oneshot} );
        } else {
            if ( func == nullptr ) {
                // Need to remove from the list
                if ( subkey.size() == 0 ) {
                    // remove all
                    sub_map_.erase(_sit);
                } else {
                    // loop to compare the subkey
                    for (
                        auto _s = _sit->second.begin();
                        _s != _sit->second.end();
                        /* void */
                    ) {
                        if ( _s->subkey == subkey ) {
                            _s = _sit->second.erase(_s);
                        } else {
                            ++_s;
                        }
                    }
                }
            } else {
                // add to tail
                _sit->second.emplace_back( ItemSubscriberInfo{subkey, func, is_oneshot} );
            }
        }
    }

    void Subscribe( ItemKey key, SubscriberFunc func, bool oneshot = false) {
        this->Subscribe(key, func, oneshot, std::string(""));
    }

    void Subscribe( ItemKey key, SubscriberFunc func, const std::string& subkey ) {
        this->Subscribe(key, func, false, subkey);
    }

    void Subscribe( ItemKey key, SubscriberFunc func, const char* subkey ) {
        this->Subscribe(key, func, std::string(subkey));
    }

    void SubscribeOnce( ItemKey key, SubscriberFunc func ) {
        this->Subscribe(key, func, true, std::string(""));
    }

    /**
     * @brief Unregister subscribers
    */
    void Unsubscribe( ItemKey key, const std::string& subkey ) {
        this->Subscribe( key, nullptr, true, subkey );
    }

    void Unsubscribe( ItemKey key ) {
        this->Unsubscribe( key, std::string("") );
    }

    void UnsubscribeAll( ) {
        std::lock_guard< std::mutex > _(dispatcher_lock_);
        sub_map_.clear();
    }

protected: 
    mutable std::mutex status_lock_;
    mutable std::mutex dispatcher_lock_;
    bool status_;
    SubscriberMap sub_map_;
};

} // namespace basic
} // namespace bytertc
