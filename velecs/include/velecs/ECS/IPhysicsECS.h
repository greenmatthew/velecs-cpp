/// \file    IPhysicsSystems.h
/// \author  Matthew Green
/// \date    10/31/2023 18:52:56
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/ECS/IECSInterface.h"

#include <velecs/Math/Consts.h>

namespace velecs {

/// \class IPhysicsSystems
/// \brief Brief description.
///
/// Rest of description.
class IPhysicsECS : public IECSInterface {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    IPhysicsECS(IECSManager& ecsManager) : IECSInterface(ecsManager) {}
        
    /// \brief Default deconstructor.
    ~IPhysicsECS() = default;

    // Public Methods

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
