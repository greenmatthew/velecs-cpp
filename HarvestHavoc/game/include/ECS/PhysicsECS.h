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

#include "ECS/IPhysicsECS.h"

namespace hh {

/// \class PhysicsSystems
/// \brief Brief description.
///
/// Rest of description.
class PhysicsECS : public IPhysicsECS {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors
    
    PhysicsECS(flecs::world& ecs);
    
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
