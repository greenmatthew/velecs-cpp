/// \file    ECSCommon.h
/// \author  Matthew Green
/// \date    11/01/2023 19:10:21
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <flecs/flecs.h>

#include "Math/Vec2.h"
#include "Math/Vec3.h"

#include "ECS/Components/Rendering/Transform.h"
#include "ECS/Components/Rendering/Mesh.h"
#include "ECS/Components/Rendering/Material.h"
#include "ECS/Components/Rendering/OrthoCamera.h"
#include "ECS/Components/Rendering/PerspectiveCamera.h"

#include "ECS/Components/Physics/LinearKinematics.h"
#include "ECS/Components/Physics/AngularKinematics.h"

namespace hh {

/// \class ECSPipelineStages
/// \brief Brief description.
///
/// Rest of description.
struct ECSPipelineStages {
	flecs::entity InputUpdate;
	flecs::entity Update;
	flecs::entity Collisions;
	flecs::entity PreDraw;
	flecs::entity Draw;
	flecs::entity PostDraw;
	flecs::entity Housekeeping;
};

/// \class GlobalData
/// \brief Brief description.
///
/// Rest of description.
struct GlobalData {
	flecs::entity camera;
};

} // namespace hh
