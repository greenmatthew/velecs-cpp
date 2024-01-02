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

void Prefab::Init(flecs::world& world)
{
    ecs(&world);
}

flecs::world& Prefab::ecs(flecs::world* newWorld /* = nullptr */)
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




flecs::entity Prefab::Create
(
    const std::string& name,
    Transform transform
)
{
    flecs::world& world = ecs();
    flecs::entity prefab = world.prefab(name.c_str());

    transform.entity = flecs::entity::null();

    prefab.set_override<Transform>(transform);

    return prefab;
}

flecs::entity Prefab::Create
(
    const std::string& name,
    const std::optional<Vec3> pos /* = Vec3::ZERO */,
    const std::optional<Vec3> rot /* = Vec3::ZERO */,
    const std::optional<Vec3> scale /* = Vec3::ONE */
)
{
    Transform transform;

    transform.position = pos.value_or(Vec3::ZERO);
    transform.rotation = rot.value_or(Vec3::ZERO);
    transform.scale = scale.value_or(Vec3::ONE);

    return Create(name, transform);
}



flecs::entity Prefab::CreateFromPrefab
(
    const std::string& name,
    const flecs::entity prefab,
    Transform transform
)
{
    return Create(name, transform)
        .is_a(prefab);
}

flecs::entity Prefab::CreateFromPrefab
(
    const std::string& name,
    const flecs::entity prefab,
    const std::optional<Vec3> pos /* = None */,
    const std::optional<Vec3> rot /* = None */,
    const std::optional<Vec3> scale /* = None */
)
{
    const Transform* const prefabTransform = prefab.get<Transform>();
    Transform transform;

    transform.position = pos.value_or(prefabTransform->position);
    transform.rotation = rot.value_or(prefabTransform->rotation);
    transform.scale = scale.value_or(prefabTransform->scale);

    return CreateFromPrefab(name, prefab, transform);
}





flecs::entity Prefab::Find(const std::string& searchPath)
{
    flecs::world& world = ecs();

    flecs::entity prefab = world.lookup(searchPath.c_str());
    if (prefab != flecs::entity::null() && prefab.has(flecs::Prefab))
    {
        return prefab;
    }
    else
    {
        throw std::runtime_error("Invalid prefab: '" + searchPath + "'. Ensure the path is correctly formatted, "
                                 "including any necessary parent-child relationships (e.g., 'Parent::Child') and "
                                 "module prefixes (e.g., 'Module::PrefabName') if applicable.");
    }
}

bool Prefab::TryFind(const std::string& searchPath, flecs::entity* prefab, bool verbose /* = true */)
{
    try
    {
        *prefab = Find(searchPath);
    }
    catch (const std::runtime_error& e)
    {
        if (verbose)
        {
            std::cout << e.what() << std::endl;
        }
        return false;
    }
    return true;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
