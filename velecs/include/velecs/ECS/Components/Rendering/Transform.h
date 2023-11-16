/// @file    Transform.h
/// @author  Matthew Green
/// @date    10/30/2023 19:48:02
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/Math/Vec3.h"

#include <flecs.h>

namespace velecs {

/// @struct Transform
/// @brief Brief description.
///
/// Rest of description.
struct Transform {    
public:
    // Enums

    // Public Fields

    Vec3 position{Vec3::ZERO};
    Vec3 rotation{Vec3::ZERO};
    Vec3 scale{Vec3::ONE};

    // Constructors and Destructors

    /// @brief Default constructor.
    Transform() = default;

    /// @brief Default deconstructor.
    ~Transform() = default;

    // Public Methods

    const Vec3 GetAbsPosition(flecs::entity parent) const;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
