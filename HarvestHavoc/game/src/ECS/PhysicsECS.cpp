/// \file    PhysicsSystems.cpp
/// \author  Matthew Green
/// \date    10/31/2023 18:53:22
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "ECS/PhysicsECS.h"

using namespace engine;

namespace hh {

// Public Fields

// Constructors and Destructors

    PhysicsECS::PhysicsECS(flecs::world& ecs, ECSPipelineStages& stages)
    : IPhysicsECS(ecs), stages(stages) {}

// Public Methods

// Protected Fields

// Protected Methods

void PhysicsECS::InitComponents()
{
    ecs.component<Transform>();
    ecs.component<LinearKinematics>();
    ecs.component<AngularKinematics>();
}

void PhysicsECS::InitSystems()
{
    ecs.system<Transform, LinearKinematics>()
        .kind(stages.Update)
        .iter([](flecs::iter& it, Transform* transforms, LinearKinematics* linears)
            {
                float delta_time = it.delta_time();
                for (auto i : it)
                {
                    Transform& transform = transforms[i];
                    LinearKinematics& linear = linears[i];

                    linear.velocity += linear.acceleration * delta_time * delta_time;
                    transform.position += linear.velocity * delta_time;
                }
            }
    );

    ecs.system<Transform, AngularKinematics>()
        .kind(stages.Update)
        .iter([](flecs::iter& it, Transform* transforms, AngularKinematics* angulars)
            {
                float delta_time = it.delta_time();
                for (auto i : it)
                {
                    Transform& transform = transforms[i];
                    AngularKinematics& angular = angulars[i];

                    angular.angularVelocity += angular.angularAcceleration * delta_time * delta_time;
                    transform.rotation += angular.angularVelocity * delta_time;
                }
            }
    );
}

void PhysicsECS::InitEntities()
{
    ecs.entity()
        .set<Transform>({})
        .set<LinearKinematics>({ Vec3::ONE, Vec3::ZERO });
}

// Private Fields

// Private Methods

} // namespace hh
