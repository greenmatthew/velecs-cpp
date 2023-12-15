/// @file    IECSManager.h
/// @author  Matthew Green
/// @date    10/30/2023 16:21:32
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <flecs.h>

#include "velecs/VelECSEngine.h"

#include "velecs/Math/Vec3.h"

#include <string>

namespace velecs {

/// @class IECSManager
/// @brief Brief description.
///
/// Rest of description.
class IECSManager {
public:
    // Enums

    // Public Fields

    VelECSEngine& engine;
    flecs::world ecs;

    // Constructors and Destructors

    /// @brief Default constructor.
    IECSManager(VelECSEngine& engine)
        : engine(engine) {}

    /// @brief Default deconstructor.
    virtual ~IECSManager() = default;

    // Public Methods

    virtual void Init() = 0;
    virtual void Cleanup() = 0;
    virtual bool GetIsQuitting() const = 0;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
