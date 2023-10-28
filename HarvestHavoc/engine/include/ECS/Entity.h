/// \file    Entity.h
/// \author  Matthew Green
/// \date    10/27/2023 20:55:52
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "ECS/Transform.h"
#include "ECS/Component.h"

#include <string>
#include <vector>
#include <memory>

namespace engine {

/// \class Entity
/// \brief Represents an object in the game world.
///
/// An Entity is a container for Components which define its behavior and properties.
class Entity {
public:
    // Enums

    // Public Fields

    std::string name{"Unnamed Entity"}; /// \brief The name of the entity.
    Transform transform; /// \brief The transformation data of the entity including position, rotation, and scale.

    // Public Methods

    /// \brief Creates a new shared instance of Entity and returns a weak pointer to it.
    static std::weak_ptr<Entity> Create();

    /// \brief Adds a new component of type T to the entity.
    /// \tparam T The type of the component to add.
    /// \tparam Args The types of the arguments to forward to the component's constructor.
    /// \param args The arguments to forward to the component's constructor.
    /// \returns A weak pointer to the newly added component.
    template <typename T, typename... Args>
    std::weak_ptr<T> AddComponent(Args... args)
    {
        static_assert(std::is_base_of<Component, T>::value, "T is not a Component type."); // Verify that T is a subclass of Component

        for (const auto& component : components)
        {
            if (typeid(*component) == typeid(T))  // corrected here
            {
                return std::weak_ptr<T>();  // Return an empty weak_ptr if a component of type T already exists
            }
        }
        
        auto newComponent = std::make_shared<T>(this, args...);  // Assume T's constructor takes a pointer to the containing object and the additional args
        components.push_back(newComponent);
        return std::weak_ptr<T>(newComponent);
    }

    /// \brief Removes a component of type T from the entity if it exists.
    /// \tparam T The type of the component to remove.
    template <typename T>
    void RemoveComponent()
    {
        for (auto it = components.begin(); it != components.end();)
        {
            if (typeid(**it) == typeid(T))  // corrected here
            {
                it = components.erase(it);  // erase returns the iterator to the next element
                return;  // exit the function after removing the first matching component
            }
            else
            {
                ++it;  // move to the next element
            }
        }
    }

    /// \brief Removes all components from the entity.
    void RemoveAllComponents();

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    std::vector<std::shared_ptr<Component>> components; /// \brief A vector containing all the components attached to the entity.

    // Constructors and Destructors

    /// \brief Default constructor.
    Entity() = default;
    
    /// \brief Default destructor.
    ~Entity() = default;

    // Private Methods

    template<typename... Args>
    static std::shared_ptr<Entity> CreateSharedPtr(Args... args)
    {
        struct WrapperEntity : public Entity
        {
            WrapperEntity(Args... args) : Entity(args...) {};
        };

        return std::make_shared<WrapperEntity>(args...);
    }
};

} // namespace engine
