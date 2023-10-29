/// \file    DeletionQueue.h
/// \author  Matthew Green
/// \date    10/29/2023 18:19:21
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <deque>
#include <functional>

namespace engine {

/// \class DeletionQueue
/// \brief Brief description.
///
/// Rest of description.
class DeletionQueue {
public:
    // Enums

    // Public Fields

    std::deque<std::function<void()>> deletors;

    // Constructors and Destructors
    
    /// \brief Default constructor.
    DeletionQueue() = default;
    
    /// \brief Default deconstructor.
    ~DeletionQueue() = default;

    // Public Methods

    void PushDeletor(std::function<void()>&& deletor);

    void Flush();

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace engine
