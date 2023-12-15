/// @file    Prefab.cpp
/// @author  Matthew Green
/// @date    2023-11-30 16:44:31
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/ECS/Prefab.h"

namespace velecs {

// Public Fields

// Constructors and Destructors

// Public Methods

flecs::entity Prefab::Create
(
    flecs::world& ecs,
    const std::string& name /*= ""*/,
    const Vec3 position /*= Vec3::ZERO*/,
    const Vec3 rotation /*= Vec3::ZERO*/,
    const Vec3 scale /*= Vec3::ONE*/,
    const flecs::entity parent /*= flecs::entity::null()*/
)
{
    flecs::entity entity;
    if (!name.empty())
    {
        entity = ecs.prefab(name.c_str());
    }
    else
    {
        entity = ecs.prefab();
    }
    entity.set_override<Transform>({entity, position, rotation, scale});

    // If a parent was provided set it to be the child of that parent entity.
    if (parent != flecs::entity::null())
    {
        entity.child_of(parent);
    }

    return entity;
}

 flecs::entity Prefab::Create
(
    flecs::world& ecs,
    const std::string& name,
    const flecs::entity parent
)
{
    return Create(ecs, name, Vec3::ZERO, Vec3::ZERO, Vec3::ONE, parent);
}

flecs::entity Prefab::Create
(
    flecs::world& ecs,
    const flecs::entity parent,
    const Vec3 position /*= Vec3::ZERO*/,
    const Vec3 rotation /*= Vec3::ZERO*/,
    const Vec3 scale /*= Vec3::ONE*/
)
{
    return Create(ecs, "", position, rotation, scale, parent);
}

flecs::entity Prefab::Create
(
    flecs::world& ecs,
    const Vec3 position,
    const Vec3 rotation /*= Vec3::ZERO*/,
    const Vec3 scale /*= Vec3::ONE*/,
    const flecs::entity parent /*= flecs::entity::null()*/
)
{
    return Create(ecs, "", position, rotation, scale, parent);
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
