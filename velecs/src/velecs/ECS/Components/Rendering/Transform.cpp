/// @file    Transform.cpp
/// @author  Matthew Green
/// @date    2023-11-16 15:50:08
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/ECS/Components/Rendering/Transform.h"

namespace velecs {

// Public Fields

// Constructors and Destructors

// Public Methods

const Vec3 Transform::GetAbsPosition(flecs::entity parent) const
{
    Vec3 absPosition = position;
    while (parent != flecs::entity::null())
    {
        const Transform* parentTransform = parent.get<Transform>();

        // Make sure the entity actually has a Transform
        if (parentTransform)
        {
            absPosition -= parentTransform->position;
        }
        else
        {
            // If the parent does not have an entity break
            // Modules are entities, so they would give a false positive to the while condition
            break;
        }

        // Get parent's parent
        parent = parent.parent();
    }
    return absPosition;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
