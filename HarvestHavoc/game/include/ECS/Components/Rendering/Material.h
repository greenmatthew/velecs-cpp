/// \file    Material.h
/// \author  Matthew Green
/// \date    10/31/2023 12:45:31
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <Graphics/Color32.h>

namespace hh {

/// \class Material
/// \brief Brief description.
///
/// Rest of description.
struct Material {
	engine::Color32 color{engine::Color32::MAGENTA};
	VkPipeline pipeline;
	VkPipelineLayout pipelineLayout;
};

} // namespace hh
