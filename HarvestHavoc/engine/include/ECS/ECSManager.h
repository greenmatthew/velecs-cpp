/// \file    ECSManager.h
/// \author  Matthew Green
/// \date    10/27/2023 21:49:36
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "Engine/vk_engine.h"
#include "ECS/Entity.h"

#include <vector>

namespace engine {

/// \class ECSManager
/// \brief Brief description.
///
/// Rest of description.
class ECSManager {
public:
    // Enums

    // Public Fields

    // Public Methods

    static ECSManager& GetInstance()
    {
        static ECSManager instance;
        return instance;
    }

    void Init(VulkanEngine* const engine);

    void TrackEntity(std::shared_ptr<Entity> entity);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    bool isInitialized{false};
    VulkanEngine* engine{nullptr};

    // Constructors and Destructors

    ECSManager() = default;
    ~ECSManager() = default;

    // Private Methods
};

} // namespace engine
