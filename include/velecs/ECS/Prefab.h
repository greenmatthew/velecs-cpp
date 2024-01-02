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

    static void Init(flecs::world& world);

    static flecs::world& ecs(flecs::world* newWorld = nullptr);


    static flecs::entity Create
    (
        const std::string& name,
        Transform transform
    );

    static flecs::entity Create
    (
        const std::string& name,
        const std::optional<Vec3> pos = Vec3::ZERO,
        const std::optional<Vec3> rot = Vec3::ZERO,
        const std::optional<Vec3> scale = Vec3::ONE
    );

    /// @brief Retrieves a prefab entity based on a given search path.
    /// @param[in] searchPath A string representing the path to the prefab.
    /// @return The found prefab entity.
    /// @throws std::runtime_error If the prefab is not found or is invalid.
    ///
    /// @note This method looks up a prefab entity using a search path. The search path can include a path from
    /// a root prefab to a nested child (e.g., "Parent::MiddleParent::Child"), and must include a module prefix
    /// if the prefab is declared in a different module (e.g., "ECSModule::PrefabName").
    static flecs::entity Find(const std::string& searchPath);

    /// @brief Attempts to retrieve a prefab entity based on a given search path, without throwing an exception.
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
    static bool TryFind(const std::string& searchPath, flecs::entity* prefab, bool verbose = true);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
