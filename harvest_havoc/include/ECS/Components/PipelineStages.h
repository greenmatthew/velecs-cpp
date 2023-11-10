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

#include <flecs/flecs.h>

namespace hh {

/// @class PipelineStages
/// @brief Brief description.
///
/// Rest of description.
struct PipelineStages {
    flecs::entity InputUpdate;
	flecs::entity Update;
	flecs::entity Collisions;
	flecs::entity PreDraw;
	flecs::entity Draw;
	flecs::entity PostDraw;
	flecs::entity Housekeeping;
};

} // namespace hh
