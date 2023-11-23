/// @file    CommonECSModule.cpp
/// @author  Matthew Green
/// @date    2023-11-15 13:08:59
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/ECS/Modules/CommonECSModule.h"

#include <iostream>

namespace velecs {

// Public Fields

// Constructors and Destructors

CommonECSModule::CommonECSModule(flecs::world& ecs)
{
    ecs.import<CommonECSModule>();
    std::cout << "[INFO] [ECSManager] Started import of '" << typeid(CommonECSModule).name() << "' ECS module on flecs::world::id(): " << ecs.id() << " @ 0x" << ecs.c_ptr() << '.' << std::endl;

    ecs.component<Transform>();

    flecs::entity ep = ecs.prefab("PR_Entity")
        .override<Transform>();
}

// Public Methods

flecs::entity CommonECSModule::GetPrefab(flecs::world& ecs, const std::string& searchPath)
{
    flecs::entity prefab = ecs.lookup(searchPath.c_str());
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

bool CommonECSModule::TryGetPrefab(flecs::world& ecs, const std::string& searchPath, flecs::entity* prefab, bool verbose /* = true */)
{
    try
    {
        *prefab = GetPrefab(ecs, searchPath);
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



flecs::entity CommonECSModule::CreateEntity
(
    flecs::world& ecs,
    const std::string& name,
    flecs::entity& parent
)
{
    return CreateEntity(ecs, name, Vec3::ZERO, Vec3::ZERO, parent);
}

flecs::entity CommonECSModule::CreateEntity
(
    flecs::world& ecs,
    const std::string& name,
    const Vec3 position,
    const Vec3 rotation /* = Vec3::ZERO */,
    flecs::entity& parent /* = flecs::entity::null() */
)
{
    flecs::entity entity = ecs.prefab("Entity")
        .set_name(name.c_str())
        .override<Transform>();
    
    entity.set<Transform>({entity, position, rotation});

    if (parent != flecs::entity::null())
    {
        if (parent.is_valid())
        {
            entity.child_of(parent);
        }
        else
        {
            std::exception("Parent is not a valid entity.");
        }
    }

    return entity;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
