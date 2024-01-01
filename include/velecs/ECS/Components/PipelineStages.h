/// @file    PipelineStages.h
/// @author  Matthew Green
/// @date    2023-11-09 16:15:49
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <flecs.h>

namespace velecs {

/// @struct PipelineStages
/// @brief Brief description.
///
/// Rest of description.
struct PipelineStages {
public:
    // Enums

    // Public Fields

    flecs::entity InputUpdate;
	flecs::entity Update;
	flecs::entity Collisions;
	flecs::entity PreDraw;
	flecs::entity Draw;
	flecs::entity PostDraw;
	flecs::entity Housekeeping;

    flecs::entity FinalCleanup;

    // Constructors and Destructors

    /// @brief Default constructor.
    PipelineStages() = default;

    /// @brief Default deconstructor.
    ~PipelineStages() = default;

    // Public Methods

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
