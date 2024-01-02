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

void Entity::Init(flecs::world& world)
{
    ecs(&world);
}

flecs::world& Entity::ecs(flecs::world* newWorld /* = nullptr */)
{
    static flecs::world* worldPtr = nullptr;  // Static pointer to hold the world reference
    
    if (newWorld != nullptr)
    {
        if (worldPtr == nullptr)
        {
            worldPtr = newWorld;  // Set the world pointer if it hasn't been set
        }
        else
        {
            throw std::runtime_error("World is already initialized.");  // Prevent reinitialization
        }
    }
    else if (worldPtr == nullptr)
    {
        throw std::runtime_error("World is not initialized yet.");  // Ensure it's initialized before usage
    }
    
    return *worldPtr;  // Return a reference to the stored world object
}

flecs::entity Entity::Create
(
    Transform transform,
    const std::optional<flecs::entity> parent /* = None */
)
{
    flecs::world& world = ecs();
    flecs::entity entity = world.entity();

    transform.entity = entity;

    entity.set_override<Transform>(transform);

    if (parent)
    {
        entity.child_of(parent.value());
    }

    return entity;
}

flecs::entity Entity::Create
(
    const std::optional<Vec3> pos /* = Vec3::ZERO */,
    const std::optional<Vec3> rot /* = Vec3::ZERO */,
    const std::optional<Vec3> scale /* = Vec3::ONE */,
    const std::optional<flecs::entity> parent /* = None */
)
{
    Transform transform;

    transform.position = pos.value_or(Vec3::ZERO);
    transform.rotation = rot.value_or(Vec3::ZERO);
    transform.scale = scale.value_or(Vec3::ONE);

    return Create(transform, parent);
}

flecs::entity Entity::Create
(
    const flecs::entity parent,
    const std::optional<Vec3> pos /* = Vec3::ZERO */,
    const std::optional<Vec3> rot /* = Vec3::ZERO */,
    const std::optional<Vec3> scale /* = Vec3::ONE */
)
{
    return Create(pos, rot, scale, parent);
}



flecs::entity Entity::CreateFromPrefab
(
    const flecs::entity prefab,
    Transform transform,
    std::optional<flecs::entity> parent /* = None */
)
{
    return Create(transform, parent)
        .is_a(prefab);
}

flecs::entity Entity::CreateFromPrefab
(
    const flecs::entity prefab,
    const std::optional<Vec3> pos /* = Vec3::ZERO */,
    const std::optional<Vec3> rot /* = Vec3::ZERO */,
    const std::optional<Vec3> scale /* = Vec3::ONE */,
    const std::optional<flecs::entity> parent /* = None */
)
{
    return Create(pos, rot, scale, parent)
        .is_a(prefab);
}

flecs::entity Entity::CreateFromPrefab
(
    const flecs::entity prefab,
    const flecs::entity parent,
    const std::optional<Vec3> pos /* = Vec3::ZERO */,
    const std::optional<Vec3> rot /* = Vec3::ZERO */,
    const std::optional<Vec3> scale /* = Vec3::ONE */
)
{
    return CreateFromPrefab(prefab, pos, rot, scale, parent);
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
