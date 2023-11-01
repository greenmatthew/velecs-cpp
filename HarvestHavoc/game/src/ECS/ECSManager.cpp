/// \file    ECSManager.cpp
/// \author  Matthew Green
/// \date    10/30/2023 16:17:43
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "ECS/ECSManager.h"

#include "ECS/PhysicsECS.h"
#include "ECS/RenderingECS.h"

#include "ECS/Components/Rendering/Transform.h"
#include "ECS/Components/Physics/LinearKinematics.h"
#include "ECS/Components/Physics/AngularKinematics.h"

using namespace engine;

namespace hh {

// Public Fields

// Constructors and Destructors

ECSManager::ECSManager(engine::VulkanEngine& engine)
    : physicsECS(std::make_unique<PhysicsECS>(ecs)),
        renderingECS(std::make_unique<RenderingECS>(ecs, engine)) {}

// Public Methods

void ECSManager::Init()
{
    InitPipeline();

    physicsECS->Init();
    renderingECS->Init();
}

void ECSManager::Cleanup()
{
    renderingECS->Cleanup();
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

void ECSManager::InitPipeline()
{
    // Create a custom pipeline that includes your custom phases
    flecs::entity pipeline = ecs.pipeline()
        .with(flecs::System)  // Mandatory, must always match systems
        .with<InputUpdate>().or_()
        .with<Update>().or_()
        .with<Collisions>().or_()
        .with<PreDraw>().or_()
        .with<Draw>().or_()
        .with<PostDraw>().or_()
        .with<HouseKeeping>()
        .build();

    // Set the custom pipeline on the world
    ecs.set_pipeline(pipeline);

    // InputUpdate Stage
    //ecs.system()
    //    .kind<InputUpdate>()
    //    .iter([](flecs::iter& it) {
    //        std::cout << "Running InputUpdate Stage" << std::endl;
    //    });

    //// Update Stage
    //ecs.system()
    //    .kind<Update>()
    //    .iter([](flecs::iter& it) {
    //        std::cout << "Running Update Stage" << std::endl;
    //    });

    //// Collisions Stage
    //ecs.system()
    //    .kind<Collisions>()
    //    .iter([](flecs::iter& it) {
    //        std::cout << "Running Collisions Stage" << std::endl;
    //    });

    //// Draw Stage
    //ecs.system()
    //    .kind<Draw>()
    //    .iter([](flecs::iter& it) {
    //        std::cout << "Running Draw Stage" << std::endl;
    //    });

    //// HouseKeeping Stage
    //ecs.system()
    //    .kind<HouseKeeping>()
    //    .iter([](flecs::iter& it) {
    //        std::cout << "Running HouseKeeping Stage" << std::endl;
    //    });
}

} // namespace hh
