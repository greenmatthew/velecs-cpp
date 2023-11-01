/// \file    RenderingSystems.h
/// \author  Matthew Green
/// \date    10/31/2023 12:32:09
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "ECS/IRenderingECS.h"

namespace hh {

/// \class RenderingSystems
/// \brief Brief description.
///
/// Rest of description.
class RenderingECS : public IRenderingECS {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    RenderingECS(flecs::world& ecs, engine::VulkanEngine& engine);
    
    /// \brief Default deconstructor.
    ~RenderingECS() = default;

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

    glm::mat4 GetRenderMatrix(const Mesh& mesh, const Material& material) override;
};

} // namespace hh
