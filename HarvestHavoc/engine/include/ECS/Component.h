/// \file    Component.h
/// \author  Matthew Green
/// \date    10/27/2023 20:59:45
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <memory>

namespace engine {

class Entity;

/// \class Component
/// \brief Brief description.
///
/// Rest of description.
class Component {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors
    
    Component(std::weak_ptr<Entity> entity);
    
    /// \brief Default deconstructor.
    ~Component() = default;

    // Public Methods

    std::weak_ptr<Entity> GetEntity();

protected:
    // Protected Fields

    std::weak_ptr<Entity> entity;

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace engine
