/// @file    PhysicsECSModule.cpp
/// @author  Matthew Green
/// @date    2023-11-13 16:24:11
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "ECS/Modules/PhysicsECSModule.h"

#include "ECS/Components/Rendering/Transform.h"

#include "ECS/Components/Physics/LinearKinematics.h"
#include "ECS/Components/Physics/AngularKinematics.h"

#include "ECS/Components/PipelineStages.h"

#include <velecs/Math/Vec3.h>

using namespace velecs;

namespace hh {

void Test1(flecs::entity e, Transform& input)
{
    std::cout << "Test1" << std::endl;
}

void Test2(flecs::entity e, Transform& input)
{
    std::cout << "Test2" << std::endl;
}

// Public Fields

// Constructors and Destructors

PhysicsECSModule::PhysicsECSModule(flecs::world& ecs)
    : IECSModule(ecs)
{
    // ecs.module<PhysicsECSModule>();

    // auto stages = ecs.singleton<PipelineStages>().get<PipelineStages>();

    ecs.component<Transform>();
    ecs.component<LinearKinematics>();
    ecs.component<AngularKinematics>();

    ecs.system<Transform, LinearKinematics>()
        .kind(stages->Update)
        .iter([](flecs::iter& it, Transform* transforms, LinearKinematics* linears)
            {
                float deltaTime = it.delta_time();
                for (auto i : it)
                {
                    Transform& transform = transforms[i];
                    LinearKinematics& linear = linears[i];

                    linear.velocity += linear.acceleration * deltaTime * deltaTime;
                    transform.position += linear.velocity * deltaTime;

                    //auto entity = it.entity(i);
                    //const char* entityName = entity.name();
                    //if (entityName)
                    //{
                    //    std::cout << "name: " << entityName << std::endl;
                    //}
                    //else
                    //{
                    //    std::cout << "name: n/a" << std::endl;
                    //}
                    //std::cout << "id: " << entity.id() << std::endl;
                    //std::cout << "vel: " << linear.velocity << std::endl;
                    //std::cout << "pos: " << transform.position << '\n' << std::endl;
                }
            }
    );

    ecs.system<Transform, AngularKinematics>()
        .kind(stages->Update)
        .iter([](flecs::iter& it, Transform* transforms, AngularKinematics* angulars)
            {
                float deltaTime = it.delta_time();
                for (auto i : it)
                {
                    Transform& transform = transforms[i];
                    AngularKinematics& angular = angulars[i];

                    angular.angularVelocity += angular.angularAcceleration * deltaTime * deltaTime;
                    transform.rotation += angular.angularVelocity * deltaTime;
                }
            }
    );
}



// Public Methods

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace hh
