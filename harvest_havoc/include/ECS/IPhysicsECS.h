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

#include <velecs/Math/Consts.h>

#include "ECS/IECSInterface.h"


namespace hh {

/// \class IPhysicsSystems
/// \brief Brief description.
///
/// Rest of description.
class IPhysicsECS : public IECSInterface {
public:
    // Enums

    // Public Fields

    // Destructors
        
    /// \brief Default deconstructor.
    ~IPhysicsECS() = default;

    // Public Methods

protected:
    // Protected Fields

    // Constructors

    IPhysicsECS(flecs::world& ecs) : IECSInterface(ecs) {}

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace hh
