/// @file    PipelineECSModule.cpp
/// @author  Matthew Green
/// @date    2023-11-13 17:14:50
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "ECS/PipelineECSModule.h"

namespace hh {

// Public Fields

// Constructors and Destructors

PipelineECSModule::PipelineECSModule(flecs::world& ecs)
{
    ecs.module<PipelineECSModule>();

    ecs.component<PipelineStages>();

    auto inputUpdate = ecs.entity("InputUpdatePhase").add(flecs::Final).add(flecs::Phase);
    auto update = ecs.entity("UpdatePhase").add(flecs::Final).add(flecs::Phase).depends_on(inputUpdate);
    auto collisions = ecs.entity("CollisionsPhase").add(flecs::Final).add(flecs::Phase).depends_on(update);
    auto preDraw = ecs.entity("PreDrawPhase").add(flecs::Final).add(flecs::Phase).depends_on(collisions);
    auto draw = ecs.entity("DrawPhase").add(flecs::Final).add(flecs::Phase).depends_on(preDraw);
    auto postDraw = ecs.entity("PostDrawPhase").add(flecs::Final).add(flecs::Phase).depends_on(draw);
    auto housekeeping = ecs.entity("HousekeepingPhase").add(flecs::Final).add(flecs::Phase).depends_on(postDraw);

    ecs.set<PipelineStages>
    (
        {
            inputUpdate,
            update,
            collisions,
            preDraw,
            draw,
            postDraw,
            housekeeping
        }
    );
    
    auto pipeline = ecs.pipeline()
        .with(flecs::System)
        .with(flecs::Phase)
        .cascade(flecs::DependsOn)
        .build();
    ecs.set_pipeline(pipeline);

    // Add dummy systems backwards to the order of the phases
    // to ensure no false positives

    // auto stages = ecs.singleton<PipelineStages>().get<PipelineStages>();

    // ecs.system()
    //    .kind(stages->Housekeeping)
    //    .iter([](flecs::iter& it) {
    //        std::cout << "Running HouseKeeping Stage" << std::endl;
    //    });
    
    // ecs.system()
    //     .kind(stages->PostDraw)
    //     .iter([](flecs::iter& it) {
    //         std::cout << "Running Post Draw Stage" << std::endl;
    //     });
    
    // ecs.system()
    //    .kind(stages->Draw)
    //    .iter([](flecs::iter& it) {
    //        std::cout << "Running Draw Stage" << std::endl;
    //    });
    
    // ecs.system()
    //     .kind(stages->PreDraw)
    //     .iter([](flecs::iter& it) {
    //         std::cout << "Running Pre Draw Stage" << std::endl;
    //     });
    
    // ecs.system()
    //    .kind(stages->Collisions)
    //    .iter([](flecs::iter& it) {
    //        std::cout << "Running Collisions Stage" << std::endl;
    //    });

    // ecs.system()
    //    .kind(stages->Update)
    //    .iter([](flecs::iter& it) {
    //        std::cout << "Running Update Stage" << std::endl;
    //    });
    
    // ecs.system()
    //    .kind(stages->InputUpdate)
    //    .iter([](flecs::iter& it) {
    //        std::cout << "Running InputUpdate Stage" << std::endl;
    //    });
}

// Public Methods

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace hh
