/// @file    Entity.h
/// @author  Matthew Green
/// @date    2023-11-30 16:43:58
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/ECS/Components/Rendering/Transform.h"

#include <flecs.h>

namespace velecs {

/// @class Entity
/// @brief Brief description.
///
/// Rest of description.
class Entity {
public:
    // Enums

    // Public Fields

    // Deleted constructors and assignment operators
    Entity() = delete;
    ~Entity() = delete;
    Entity(const Entity&) = delete;
    Entity(Entity&&) = delete;
    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&&) = delete;

    // Public Methods

    // static flecs::entity CreateNoTransform(flecs::world& ecs);

    // static flecs::entity Create
    // (
    //     flecs::world& ecs,
    //     const Vec3 position = Vec3::ZERO,
    //     const Vec3 rotation = Vec3::ZERO,
    //     const Vec3 scale = Vec3::ONE,
    //     const std::string& name = ""
    // );

    static flecs::entity Create
    (
        flecs::world& ecs,
        const std::string& name = "",
        const Vec3 position = Vec3::ZERO,
        const Vec3 rotation = Vec3::ZERO,
        const Vec3 scale = Vec3::ONE,
        const flecs::entity parent = flecs::entity::null()
    );

    static flecs::entity Create
    (
        flecs::world& ecs,
        const std::string& name,
        const flecs::entity parent
    );

    static flecs::entity Create
    (
        flecs::world& ecs,
        const flecs::entity parent
    );

    static flecs::entity Create
    (
        flecs::world& ecs,
        const Vec3 position = Vec3::ZERO,
        const Vec3 rotation = Vec3::ZERO,
        const Vec3 scale = Vec3::ONE,
        const flecs::entity parent = flecs::entity::null()
    );

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
