/// @file    CommonECSModule.h
/// @author  Matthew Green
/// @date    2023-11-15 13:00:34
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

/// @struct CommonECSModule
/// @brief Brief description.
///
/// Rest of description.
struct CommonECSModule {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    /// @brief Constructor.
    CommonECSModule(flecs::world& ecs);

    /// @brief Default deconstructor.
    ~CommonECSModule() = default;

    // Public Methods

    /// @brief Retrieves a prefab entity based on a given search path.
    /// @param[in] ecs The ECS world in which the search is conducted.
    /// @param[in] searchPath A string representing the path to the prefab.
    /// @return The found prefab entity.
    /// @throws std::runtime_error If the prefab is not found or is invalid.
    ///
    /// @note This method looks up a prefab entity using a search path. The search path can include a path from
    /// a root prefab to a nested child (e.g., "Parent::MiddleParent::Child"), and must include a module prefix
    /// if the prefab is declared in a different module (e.g., "ECSModule::PrefabName").
    static flecs::entity GetPrefab(flecs::world& ecs, const std::string& searchPath);

    /// @brief Attempts to retrieve a prefab entity based on a given search path, without throwing an exception.
    /// @param[in] ecs The ECS world in which the search is conducted.
    /// @param[in] searchPath A string representing the path to the prefab.
    /// @param[out] prefab Pointer to the entity where the result is stored.
    /// @param[in] verbose (Optional) Whether to print an error message to standard output if the prefab is not found.
    ///        Defaults to true.
    /// @return True if the prefab is found and valid, false otherwise.
    ///
    /// @note This method attempts to find a prefab entity using a search path. Similar to GetPrefab, the search path
    /// can include a path from a root prefab to a nested child and must include a module prefix if the prefab
    /// is declared in a different module. If the prefab is not found or invalid, and verbose is true, an error message
    /// is printed to standard output. This method does not throw an exception.
    static bool TryGetPrefab(flecs::world& ecs, const std::string& searchPath, flecs::entity* prefab, bool verbose = true);

    static flecs::entity CreateEntity
    (
        flecs::world& ecs,
        const std::string& name,
        flecs::entity& parent
    );

    static flecs::entity CreateEntity
    (
        flecs::world& ecs,
        const std::string& name,
        const Vec3 position,
        const Vec3 rotation = Vec3::ZERO,
        flecs::entity& parent = flecs::entity::null()
    );

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
