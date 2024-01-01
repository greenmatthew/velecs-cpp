/// @file    Material.h
/// @author  Matthew Green
/// @date    10/31/2023 12:45:31
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/Graphics/Color32.h"
#include "velecs/ECS/Entity.h"
#include "velecs/Core/GameExceptions.h"

#include <vulkan/vulkan_core.h>

#include <vector>

namespace velecs {

/// @struct Material
/// @brief Represents the visual and physical properties applied to an entity.
///
/// The Material struct is responsible for defining the visual appearance of an entity
/// in the game world. It encapsulates properties like color and texture, as well as
/// the Vulkan pipeline configurations.
struct Material {
    // Enums

    // Public Fields

    Color32 color{Color32::MAGENTA}; /// @brief The color of the material.
    VkPipeline* pipeline{nullptr}; /// @brief The Vulkan pipeline associated with this material.
    VkPipelineLayout* pipelineLayout{nullptr}; /// @brief The Vulkan pipeline layout associated with this material.

    // Constructors and Destructors

    /// @brief Default constructor.
    Material() = default;

    /// @brief Default deconstructor.
    ~Material() = default;

    // Public Methods

    /// @brief Creates a new Material entity in the ECS world.
    /// @param[in] ecs The ECS world where the material will be created.
    /// @param[in] path The unique path for the new material entity.
    /// @param[in] pipeline The Vulkan pipeline for the material.
    /// @param[in] pipelineLayout The Vulkan pipeline layout for the material.
    /// @param[in] color The color of the material.
    /// @return const Material* const A pointer to the newly created Material component.
    static const Material* const Create
    (
        flecs::world& ecs,
        const std::string& path,
        VkPipeline* const pipeline,
        VkPipelineLayout* const pipelineLayout,
        const Color32 color = Color32::MAGENTA
    );

    /// @brief Finds a Material component based on the search path.
    /// @param[in] ecs The ECS world where the search will be conducted.
    /// @param[in] searchPath The search path used to find the Material entity.
    /// @return const Material* const A pointer to the found Material component, if any.
    /// @throws EntitySearchPathInvalidException if the search path is invalid.
    /// @throws EntityMissingMaterialException if the entity does not have a Material component.
    static const Material* const Find(flecs::world& ecs, const std::string& searchPath);

    /// @brief Finds a mutable Material component based on the search path.
    /// @param[in] ecs The ECS world where the search will be conducted.
    /// @param[in] searchPath The search path used to find the Material entity.
    /// @return Material* const A pointer to the found mutable Material component, if any.
    /// @throws EntitySearchPathInvalidException if the search path is invalid.
    /// @throws EntityMissingMaterialException if the entity does not have a Material component.
    static Material* const FindMut(flecs::world& ecs, const std::string& searchPath);

    /// @brief Finds an entity and returns a mutable reference to its Material component.
    /// @param[in] ecs The ECS world where the entity will be searched.
    /// @param[in] searchPath The search path used to find the entity.
    /// @return Material& A mutable reference to the Material component of the found entity.
    /// @throws EntitySearchPathInvalidException if the search path is invalid.
    /// @throws EntityMissingMaterialException if the entity does not have a Material component.
    static Material& FindRef(flecs::world& ecs, const std::string& searchPath);

    /// @brief Tries to find an entity and set a pointer to its Material component.
    /// @param[in] ecs The ECS world where the entity will be searched.
    /// @param[in] searchPath The search path used to find the entity.
    /// @param[out] outMaterial A pointer to the constant Material component of the found entity.
    /// @param[out] outFailureReason Optional pointer to a string where the failure reason will be stored.
    /// @return true if the entity was found and has a Material component, false otherwise.
    static bool TryFind
    (
        flecs::world& ecs,
        const std::string& searchPath,
        const Material** const outMaterial,
        std::string* outFailureReason = nullptr
    );

    /// @brief Tries to find an entity and set a pointer to its mutable Material component.
    /// @param[in] ecs The ECS world where the entity will be searched.
    /// @param[in] searchPath The search path used to find the entity.
    /// @param[out] outMaterial A pointer to the mutable Material component of the found entity.
    /// @param[out] outFailureReason Optional pointer to a string where the failure reason will be stored.
    /// @return true if the entity was found and has a mutable Material component, false otherwise.
    static bool TryFindMut
    (
        flecs::world& ecs,
        const std::string& searchPath,
        Material** const outMaterial,
        std::string* outFailureReason = nullptr
    );

    /// @brief Tries to find an entity and set a reference to its mutable Material component.
    /// @param[in] ecs The ECS world where the entity will be searched.
    /// @param[in] searchPath The search path used to find the entity.
    /// @param[out] outMaterial A reference to the mutable Material component of the found entity.
    /// @param[out] outFailureReason Optional pointer to a string where the failure reason will be stored.
    /// @return true if the entity was found and has a mutable Material component, false otherwise.
    static bool TryFindRef
    (
        flecs::world& ecs,
        const std::string& searchPath,
        Material& outMaterial,
        std::string* outFailureReason = nullptr
    );

    void Cleanup(VkDevice device)
    {
        if (pipeline != VK_NULL_HANDLE)
        {
            vkDestroyPipeline(device, *pipeline, nullptr);
            *pipeline = VK_NULL_HANDLE;
        }

        if (pipelineLayout != VK_NULL_HANDLE)
        {
            vkDestroyPipelineLayout(device, *pipelineLayout, nullptr);
            *pipelineLayout = VK_NULL_HANDLE;
        }
    }

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods

    /// @brief Finds an entity with a Material component based on the search path.
    /// @param[in] ecs The ECS world where the entity will be searched.
    /// @param[in] searchPath The search path used to find the entity.
    /// @return flecs::entity The found entity with a Material component.
    /// @throws EntitySearchPathInvalidException if the search path is invalid.
    /// @throws EntityMissingMaterialException if the entity does not have a Material component.
    static flecs::entity FindEntity(flecs::world& ecs, const std::string& searchPath);

    /// @brief Attempts to find an entity with a Material component based on the search path and optionally provides the reason for failure if not found.
    /// @param[in] ecs The ECS world where the entity will be searched.
    /// @param[in] searchPath The search path used to find the entity.
    /// @param[out] outEntity The found entity, or null if not found.
    /// @param[out] outFailureReason A pointer to a string where the failure reason will be stored if provided.
    /// @return true if the entity was found successfully, false otherwise.
    /// @note This function attempts to find an entity using the provided search path.
    /// If the entity is found and has a Material component, it sets outEntity to this entity and returns true.
    /// If the entity is not found or doesn't have a Material component, it sets outFailureReason (if provided)
    /// to an appropriate error message and returns false.
    static bool TryFindEntity
    (
        flecs::world& ecs,
        const std::string& searchPath,
        flecs::entity& outEntity,
        std::string* outFailureReason = nullptr
    );
};

} // namespace velecs
