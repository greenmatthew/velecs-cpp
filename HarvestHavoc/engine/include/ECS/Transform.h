/// \file    Transform.h
/// \author  Matthew Green
/// \date    10/27/2023 17:33:18
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "Math/Vec3.h"

namespace engine {

/// \class Transform
/// \brief Brief description.
///
/// Rest of description.
class Transform {
public:
    // Enums

    // Public Fields

    Vec3 position{Vec3::ZERO};
    Vec3 rotation{Vec3::ZERO};
    Vec3 scale{Vec3::ONE};

    // Constructors and Destructors
    
    /// \brief Default constructor.
    Transform() = default;
    
    /// \brief Default deconstructor.
    ~Transform() = default;

    // Public Methods

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace engine
