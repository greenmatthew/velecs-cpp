/**
 * \file        Event.h
 * \author      mgreen
 * \date        10/18/2023 13:01:36
 * 
 * \section     LICENSE
 * 
 * Copyright (c) 2023 Matthew Green - All rights reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once


#include <vector>
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace HarvestHavoc {

/**
 * \brief Manages a list of callbacks.
 *
 * The Event class is a template class that manages a list of callbacks.
 * The callbacks can be added, removed, and invoked with specified arguments.
 */
template<typename... Args>
class Event {
public:
    /**
     * \brief Defines the type of function that can be registered as a callback.
     */
    using EventCallback = std::function<void(Args...)>;
    
    /**
     * \brief Unique identifier for each callback.
     */
    using CallbackId = std::size_t;    

    // Enums

    // Public Fields

    // Constructors and Destructors
    
    /**
     * \brief Default constructor.
     */
    Event() = default;
    
    /**
     * \brief Default destructor.
     */
    ~Event() = default;

    // Public Methods
    
    /**
     * \brief Registers a new callback using the += operator.
     * 
     * \param callback The callback function to register.
     * \return Reference to this Event instance.
     */
    Event& operator+=(const EventCallback& callback)
    {
        AddListener(callback);
        return *this;
    }

    /**
     * \brief Registers a new callback.
     * 
     * \param callback The callback function to register.
     * \return The unique identifier assigned to the callback.
     */
    CallbackId AddListener(const EventCallback& callback)
    {
        CallbackId id = nextCallbackId++;
        callbacks[id] = callback;
        return id;
    }

    /**
     * \brief Unregisters a callback using the -= operator.
     * 
     * \param id The unique identifier of the callback to unregister.
     * \return Reference to this Event instance.
     */
    Event& operator-=(const CallbackId id)
    {
        RemoveListener(id);
        return *this;
    }

    /**
     * \brief Unregisters a callback.
     * 
     * \param id The unique identifier of the callback to unregister.
     */
    void RemoveListener(const CallbackId id)
    {
        auto it = callbacks.find(id);
        if (it != callbacks.end())
        {
            callbacks.erase(it);
        }
        else
        {
            throw std::out_of_range("[Event] Unable to remove listener: No listener found with id " + std::to_string(id) + ".");
        }
    }

    /**
     * \brief Unregisters all callbacks.
     */
    void RemoveAllListeners()
    {
        callbacks.clear();
    }

    /**
     * \brief Invokes all registered callbacks with the specified arguments.
     * 
     * \param args The arguments to pass to each callback.
     */
    void Invoke(const Args&... args) const
    {
        for (const auto& [id, callback] : callbacks)
        {
            callback(args...);
        }
    }

protected:
    // Protected Fields

    // Protected Methods

private:
    /**
     * \brief Map of registered callbacks keyed by their unique identifiers.
     */
    std::unordered_map<CallbackId, EventCallback> callbacks;
    
    /**
     * \brief The next available unique identifier for callbacks.
     */
    CallbackId nextCallbackId = 0;

    // Private Methods
};

} // namespace HarvestHavoc
