/// \file    IECSManager.h
/// \author  Matthew Green
/// \date    10/30/2023 16:21:32
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <flecs/flecs.h>

#include "velecs/VelECSEngine.h"

#include "velecs/ECS/IRenderingECS.h"
#include "velecs/ECS/IPhysicsECS.h"

#include <memory>

namespace velecs {

/// \class IECSManager
/// \brief Brief description.
///
/// Rest of description.
class IECSManager {
public:
    // Enums

    // Public Fields

    VelECSEngine& engine;
    flecs::world ecs;
    std::unique_ptr<IRenderingECS> renderingECS;
    std::unique_ptr<IPhysicsECS> physicsECS;

    // Constructors and Destructors

    /// \brief Default constructor.
    IECSManager(velecs::VelECSEngine& engine, std::unique_ptr<IRenderingECS> renderingECS, std::unique_ptr<IPhysicsECS> physicsECS)
        : engine(engine), renderingECS(std::move(renderingECS)), physicsECS(std::move(physicsECS)) {}

    /// \brief Default deconstructor.
    virtual ~IECSManager() = default;

    // Public Methods

    virtual void Init() = 0;
    virtual void Cleanup() = 0;

protected:
    // Protected Fields

    // Protected Methods

    virtual void InitPipeline() = 0;

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
