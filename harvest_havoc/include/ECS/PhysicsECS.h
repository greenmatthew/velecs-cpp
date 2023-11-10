/// \file    PhysicsSystems.h
/// \author  Matthew Green
/// \date    10/31/2023 18:53:05
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <velecs/ECS/IPhysicsECS.h>

#include "ECS/ECSCommon.h"

namespace hh {

/// \class PhysicsSystems
/// \brief Brief description.
///
/// Rest of description.
class PhysicsECS : public velecs::IPhysicsECS {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors
    
    PhysicsECS(ECSManager& ecsManager);
    
    /// \brief Default deconstructor.
    ~PhysicsECS() = default;

    // Public Methods

protected:
    // Protected Fields

    // Protected Methods

    void InitComponents() override;
    void InitSystems() override;
    void InitEntities() override;

private:
    // Private Fields

    // Private Methods
};

} // namespace hh
