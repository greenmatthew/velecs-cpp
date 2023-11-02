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

using namespace velecs;

namespace hh {

// Public Fields

// Constructors and Destructors

ECSManager::ECSManager(velecs::VelECSEngine& engine)
    : physicsECS(std::make_unique<PhysicsECS>(ecs, stages)),
        renderingECS(std::make_unique<RenderingECS>(ecs, stages, engine)) {}

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
    auto pipeline = ecs.pipeline()
        .with(flecs::System)
        .with(flecs::Phase)
        .cascade(flecs::DependsOn)
        .build();
    
    stages.InputUpdate = ecs.entity("InputUpdatePhase")
        .add(flecs::Final)
        .add(flecs::Phase)
        .depends_on(pipeline);

    stages.Update = ecs.entity("UpdatePhase")
        .add(flecs::Final)
        .add(flecs::Phase)
        .depends_on(stages.InputUpdate);
    
    stages.Collisions = ecs.entity("CollisionsPhase")
        .add(flecs::Final)
        .add(flecs::Phase)
        .depends_on(stages.Update);
    
    stages.PreDraw = ecs.entity("PreDrawPhase")
        .add(flecs::Final)
        .add(flecs::Phase)
        .depends_on(stages.Collisions);

    stages.Draw = ecs.entity("DrawPhase")
        .add(flecs::Final)
        .add(flecs::Phase)
        .depends_on(stages.PreDraw);

    stages.PostDraw = ecs.entity("PostDrawPhase")
        .add(flecs::Final)
        .add(flecs::Phase)
        .depends_on(stages.Draw);
    
    stages.Housekeeping = ecs.entity("HousekeepingPhase")
        .add(flecs::Final)
        .add(flecs::Phase)
        .depends_on(stages.PostDraw);

    // Set the custom pipeline on the world
    ecs.set_pipeline(pipeline);

    // Add dummy systems backwards to the order of the phases
    // to ensure no false positives

    // ecs.system()
    //    .kind(stages.Housekeeping)
    //    .iter([](flecs::iter& it) {
    //        std::cout << "Running HouseKeeping Stage" << std::endl;
    //    });
    
    // ecs.system()
    //     .kind(stages.PostDraw)
    //     .iter([](flecs::iter& it) {
    //         std::cout << "Running Post Draw Stage" << std::endl;
    //     });
    
    // ecs.system()
    //    .kind(stages.Draw)
    //    .iter([](flecs::iter& it) {
    //        std::cout << "Running Draw Stage" << std::endl;
    //    });
    
    // ecs.system()
    //     .kind(stages.PreDraw)
    //     .iter([](flecs::iter& it) {
    //         std::cout << "Running Pre Draw Stage" << std::endl;
    //     });
    
    // ecs.system()
    //    .kind(stages.Collisions)
    //    .iter([](flecs::iter& it) {
    //        std::cout << "Running Collisions Stage" << std::endl;
    //    });

    // ecs.system()
    //    .kind(stages.Update)
    //    .iter([](flecs::iter& it) {
    //        std::cout << "Running Update Stage" << std::endl;
    //    });
    
    // ecs.system()
    //    .kind(stages.InputUpdate)
    //    .iter([](flecs::iter& it) {
    //        std::cout << "Running InputUpdate Stage" << std::endl;
    //    });
}

} // namespace hh
