/// @file    Material.cpp
/// @author  Matthew Green
/// @date    2023-12-31 15:42:36
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/ECS/Components/Rendering/Material.h"

namespace velecs {

// Public Fields

// Constructors and Destructors

// Public Methods

const Material* const Material::Create
(
    flecs::world& ecs,
    const std::string& path,
    VkPipeline* const pipeline,
    VkPipelineLayout* const pipelineLayout,
    const Color32 color /*= Color32::MAGENTA*/
)
{
    flecs::entity entity = ecs.entity(path.c_str())
        .is_a<Material>()
        .set<Material>({color, pipeline, pipelineLayout})
        ;
    return entity.get<Material>();
}

const Material* const Material::Find(flecs::world& ecs, const std::string& searchPath)
{
    return FindEntity(ecs, searchPath).get<Material>();
}

Material* const Material::FindMut(flecs::world& ecs, const std::string& searchPath)
{
    return FindEntity(ecs, searchPath).get_mut<Material>();
}

Material& Material::FindRef(flecs::world& ecs, const std::string& searchPath)
{
    return *FindEntity(ecs, searchPath).get_ref<Material>().get();
}

bool Material::TryFind
(
    flecs::world& ecs,
    const std::string& searchPath,
    const Material** const outMaterial,
    std::string* outFailureReason /*= nullptr*/
)
{
    flecs::entity entity = flecs::entity::null();
    if (TryFindEntity(ecs, searchPath, entity, outFailureReason))
    {
        *outMaterial = entity.get<Material>();
        return true;
    }
    else
    {
        return false;
    }
}

bool Material::TryFindMut
(
    flecs::world& ecs,
    const std::string& searchPath,
    Material** const outMaterial,
    std::string* outFailureReason /*= nullptr*/
)
{
    flecs::entity entity = flecs::entity::null();
    if (TryFindEntity(ecs, searchPath, entity, outFailureReason))
    {
        *outMaterial = entity.get_mut<Material>();
        return true;
    }
    else
    {
        return false;
    }
}


bool Material::TryFindRef
(
    flecs::world& ecs,
    const std::string& searchPath,
    Material& outMaterial,
    std::string* outFailureReason /*= nullptr*/
)
{
    flecs::entity entity = flecs::entity::null();
    if (TryFindEntity(ecs, searchPath, entity, outFailureReason))
    {
        outMaterial = *entity.get_ref<Material>().get();
        return true;
    }
    else
    {
        return false;
    }
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

flecs::entity Material::FindEntity(flecs::world& ecs, const std::string& searchPath)
{
    flecs::entity entity = Entity::Find(ecs, searchPath);
    if (!entity.has<Material>())
    {
        throw EntityMissingMaterialException<Material>(searchPath);
    }
    return entity;
}

bool Material::TryFindEntity
(
    flecs::world& ecs,
    const std::string& searchPath,
    flecs::entity& outEntity,
    std::string* outFailureReason /*= nullptr*/
)
{
    std::string failureReason;
    try
    {
        outEntity = FindEntity(ecs, searchPath);
        return true;
    }
    catch (const EntitySearchPathInvalidException<Entity>& e)
    {
        failureReason = e.what();
    }
    catch (const EntityMissingMaterialException<Material>& e)
    {
        failureReason = e.what();
    }
    if (outFailureReason)
    {
        *outFailureReason = failureReason;
    }
    return false;
}

} // namespace velecs
