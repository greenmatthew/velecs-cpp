#pragma once

#include <vector>
#include <functional>
#include <stdexcept>
#include <string>

namespace HarvestHavoc
{
    namespace Input
    {
        template<typename... Args>
        class Event
        {
        protected:
            using EventCallback = std::function<void(Args...)>;
        public:
            using CallbackId = std::size_t;

        private:
            std::unordered_map<CallbackId, EventCallback> callbacks;
            CallbackId nextCallbackId = 0;

        public:
            Event() = default;
            ~Event() = default;

            CallbackId AddListener(const EventCallback& callback)
            {
                CallbackId id = nextCallbackId++;
                callbacks[id] = callback;
                return id;
            }

            void Invoke(const Args&... args) const
            {
                for (const auto& [id, callback] : callbacks)
                {
                    callback(args...);
                }
            }

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

            void RemoveAllListeners()
            {
                callbacks.clear();
            }
        };
    }
}