/// \file    ECSManager.h
/// \author  Matthew Green
/// \date    10/30/2023 16:17:35
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <VelECSEngine.h>

#include <ECS/IECSManager.h>

#include "ECS/ECSCommon.h"

#include "ECS/RenderingECS.h"
#include "ECS/PhysicsECS.h"

#include <functional>

namespace hh {

/// \class ECSManager
/// \brief Brief description.
///
/// Rest of description.
class ECSManager : public velecs::IECSManager {
public:
    // Enums

    // Public Fields

    ECSPipelineStages stages;

    // Constructors and Destructors
    
    /// \brief Default constructor.
    ECSManager(velecs::VelECSEngine& engine);
    
    /// \brief Default deconstructor.
    ~ECSManager() = default;

    // Public Methods

    void Init() override;

    void Cleanup() override;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    std::unique_ptr<RenderingECS> renderingECS;
    std::unique_ptr<PhysicsECS> physicsECS;

    // Private Methods

    void InitPipeline() override;
};

} // namespace hh
