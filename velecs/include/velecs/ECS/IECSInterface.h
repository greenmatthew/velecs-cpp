/// \file    IECSInterface.h
/// \author  Matthew Green
/// \date    10/31/2023 19:20:33
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <flecs.h>

namespace velecs {

class IECSManager;

/// \class IECSInterface
/// \brief Brief description.
///
/// Rest of description.
class IECSInterface {
public:
    // Enums

    // Public Fields

    // Destructors
    
    /// \brief Default deconstructor.
    ~IECSInterface() = default;

    // Public Methods

    virtual void Init();

    virtual void Cleanup() {};

protected:
    // Protected Fields

    IECSManager& ecsManager;
    flecs::world& ecs;

    // Constructors

    IECSInterface(IECSManager& ecsManager);

    // Protected Methods

    virtual void InitComponents() {}
    virtual void InitSystems() {}
    virtual void InitEntities() {}

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
