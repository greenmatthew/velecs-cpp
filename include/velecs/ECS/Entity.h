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

    /// @brief Finds an entity in the ECS system based on the given search path.
    /// 
    /// This function searches for an entity using the provided search path. If the
    /// entity is found and is not a prefab, it returns the entity. Otherwise, it
    /// throws an EntitySearchPathInvalid exception.
    /// 
    /// @param[in] ecs The ECS world where the entity will be searched.
    /// @param[in] searchPath The search path used to find the entity.
    /// @return flecs::entity The found entity.
    /// @throws EntitySearchPathInvalid<Entity> if the entity is not found or is invalid.
    static flecs::entity Find(flecs::world& ecs, const std::string& searchPath);

    /// @brief Tries to find an entity in the ECS system based on the given search path.
    /// 
    /// This function attempts to find an entity using the provided search path. It's a
    /// safer version of Find, as it doesn't throw an exception. Instead, it returns a
    /// boolean indicating success or failure and optionally provides a reason for failure.
    /// 
    /// @param[in] ecs The ECS world where the entity will be searched.
    /// @param[in] searchPath The search path used to find the entity.
    /// @param[out] outEntity The entity found (if any).
    /// @param[out] outFailureReason Optional pointer to a string where the failure reason
    ///             will be stored if the search fails and this pointer is provided.
    /// @return true if the entity was found successfully, false otherwise.
    static bool TryFind(flecs::world& ecs, const std::string& searchPath, flecs::entity& outEntity, std::string* failureReason = nullptr);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
