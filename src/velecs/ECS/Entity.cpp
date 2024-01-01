/// @file    Entity.cpp
/// @author  Matthew Green
/// @date    2023-11-30 16:44:15
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/ECS/Entity.h"
#include "velecs/Core/GameExceptions.h"

namespace velecs {

// Public Fields

// Constructors and Destructors

// Public Methods

// flecs::entity Entity::CreateNoTransform(flecs::world& ecs)
// {
//     return ecs.entity();
// }

flecs::entity Entity::Create
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
        entity = ecs.entity(name.c_str());
    }
    else
    {
        entity = ecs.entity();
    }
    entity.set_override<Transform>({entity, position, rotation, scale});

    // If a parent was provided set it to be the child of that parent entity.
    if (parent != flecs::entity::null())
    {
        entity.child_of(parent);
    }

    return entity;
}

 flecs::entity Entity::Create
(
    flecs::world& ecs,
    const std::string& name,
    const flecs::entity parent
)
{
    return Create(ecs, name, Vec3::ZERO, Vec3::ZERO, Vec3::ONE, parent);
}

flecs::entity Entity::Create
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

flecs::entity Entity::Create
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

flecs::entity Entity::Find(flecs::world& ecs, const std::string& searchPath)
{
    flecs::entity entity = ecs.lookup(searchPath.c_str());
    if (entity != flecs::entity::null() && !entity.has(flecs::Prefab))
    {
        return entity;
    }
    else
    {
        throw EntitySearchPathInvalidException<Entity>(searchPath);
    }
}

bool Entity::TryFind(flecs::world& ecs, const std::string& searchPath, flecs::entity& outEntity, std::string* outFailureReason /* = nullptr */)
{
    try
    {
        outEntity = Find(ecs, searchPath);
        return true;
    }
    catch (const EntitySearchPathInvalidException<Entity> e)
    {
        if (outFailureReason)
        {
            *outFailureReason = e.what();
        }
        return false;
    }
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
