/// @file    Prefab.h
/// @author  Matthew Green
/// @date    2023-11-30 16:44:08
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

/// @class Prefab
/// @brief Brief description.
///
/// Rest of description.
class Prefab {
public:
    // Enums

    // Public Fields

    // Deleted constructors and assignment operators
    Prefab() = delete;
    ~Prefab() = delete;
    Prefab(const Prefab&) = delete;
    Prefab(Prefab&&) = delete;
    Prefab& operator=(const Prefab&) = delete;
    Prefab& operator=(Prefab&&) = delete;

    // Public Methods

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
        const flecs::entity parent,
        const Vec3 position = Vec3::ZERO,
        const Vec3 rotation = Vec3::ZERO,
        const Vec3 scale = Vec3::ONE
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
