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

    PhysicsECS::PhysicsECS(flecs::world& ecs)
    : IPhysicsECS(ecs) {}

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
        .kind<Update>()
        .iter([](flecs::iter& it, Transform* transform, LinearKinematics* linear)
            {
                float delta_time = it.delta_time();
                for (auto i : it)
                {
                    linear[i].velocity += linear[i].acceleration * delta_time;
                    transform[i].position += linear[i].velocity * delta_time;
                    std::cout << "Entity " << it.entity(i).id() << " is at {" << transform[i].position << "}" << std::endl;
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
