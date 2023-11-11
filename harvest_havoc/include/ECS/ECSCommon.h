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

#include <flecs.h>

#include <velecs/Math/Vec2.h>
#include <velecs/Math/Vec3.h>

#include "ECS/ECSManager.h"

#include "ECS/Components/PipelineStages.h"

#include "ECS/Components/Rendering/Transform.h"
#include "ECS/Components/Rendering/Mesh.h"
#include "ECS/Components/Rendering/Material.h"
#include "ECS/Components/Rendering/OrthoCamera.h"
#include "ECS/Components/Rendering/PerspectiveCamera.h"
#include "ECS/Components/Rendering/MainCamera.h"

#include "ECS/Components/Physics/LinearKinematics.h"
#include "ECS/Components/Physics/AngularKinematics.h"
