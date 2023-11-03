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

namespace velecs {

/// \class IECSManager
/// \brief Brief description.
///
/// Rest of description.
class IECSManager {
public:
    // Enums

    // Public Fields

    flecs::world ecs;

    // Destructors

    /// \brief Default deconstructor.
    virtual ~IECSManager() = default;

    // Public Methods

    virtual void Init() = 0;
    virtual void Cleanup() = 0;

protected:
    // Protected Fields

    // Constructors

    /// \brief Default constructor.
    IECSManager() = default;

    // Protected Methods

    virtual void InitPipeline() = 0;

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
