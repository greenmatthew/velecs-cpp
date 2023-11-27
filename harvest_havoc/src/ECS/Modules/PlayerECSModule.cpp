/// @file    PlayerECSModule.cpp
/// @author  Matthew Green
/// @date    2023-11-14 16:32:44
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "ECS/Modules/PlayerECSModule.h"

#include "ECS/ECSManager.h"

#include <algorithm>

using namespace velecs;

namespace hh {

// Public Fields

// Constructors and Destructors

PlayerECSModule::PlayerECSModule(flecs::world& ecs)
    : IECSModule(ecs)
{
    ecs.import<InputECSModule>();
    ecs.import<RenderingECSModule>();
    ecs.import<PhysicsECSModule>();

    ecs.component<Nametag>();

    ecs.prefab("PR_Nametag")
        .override<Transform>()
        .override<Nametag>()
        ;

    // CreatePlayerEntity("Player");

    flecs::entity cameraEntity = RenderingECSModule::CreatePerspectiveCamera(ecs, Vec3{0.0f, 0.0f,-2.0f}, Vec3::ZERO, Vec2{1700.0f, 900.0f});
    ecs.set<MainCamera>({cameraEntity});

    flecs::entity trianglePrefab = CommonECSModule::GetPrefab(ecs, "velecs::RenderingECSModule::PR_TriangleRender");
    flecs::entity squarePrefab = CommonECSModule::GetPrefab(ecs, "velecs::RenderingECSModule::PR_SquareRender");
    flecs::entity player = ecs.entity()
        .is_a(trianglePrefab)
        .set_name("Player")
        .add<Player>()
        .add<LinearKinematics>()
        ;
    
    player.get_mut<Material>()->color = Color32::GREEN;
    
    player.get_mut<Transform>()->entity = player;
    
    cameraEntity.child_of(player);

    Transform& cameraTransform = *cameraEntity.get_ref<Transform>().get();
    flecs::entity parent = flecs::entity::null();
    if (cameraTransform.TryGetParent(parent))
    {
        std::cout << parent.name() << std::endl;
    }
    const Transform* parentTransform;
    if (cameraTransform.TryGetParentTransform(parentTransform))
    {
        std::cout << parentTransform->position << std::endl;
    }

    std::cout << cameraTransform.GetAbsPosition() << std::endl;

    // flecs::entity nametagEntity = ecs.entity()
    //     .is_a(nametagEntity)
    //     .set<Nametag>({"Test"})
    //     ;
    
    // nametagEntity.child_of(player);

    /*flecs::entity entity1 = ecs.entity()
        .is_a(trianglePrefab)
        .set_name("Entity1")
        ;
    entity1.get_mut<Transform>()->entity = entity1;
    entity1.get_mut<Transform>()->position = Vec3::UP + Vec3::RIGHT;
    entity1.get_mut<Transform>()->scale = Vec3::ONE * 0.1f;*/

    flecs::entity entity2 = ecs.entity()
        .is_a(squarePrefab)
        .set_name("Entity2")
        ;
    entity2.get_mut<Transform>()->entity = entity2;
    entity2.get_mut<Transform>()->position = Vec3::UP + Vec3::LEFT;
    entity2.get_mut<Transform>()->scale = Vec3::ONE * 0.1f;
    entity2.get_mut<Material>()->color = Color32::ORANGE;
    std::cout << entity2.get<Material>()->color << std::endl;

    /*flecs::entity entity3 = ecs.entity()
        .is_a(squarePrefab)
        .set_name("Entity3")
        ;
    entity3.get_mut<Transform>()->entity = entity3;
    entity3.get_mut<Transform>()->position = Vec3::DOWN + Vec3::RIGHT;
    entity3.get_mut<Transform>()->scale = Vec3::ONE * 0.1f;
    entity3.get_mut<Material>()->color = Color32::ORANGE;
    
    flecs::entity entity4 = ecs.entity()
        .is_a(squarePrefab)
        .set_name("Entity4")
        ;
    entity4.get_mut<Transform>()->entity = entity4;
    entity4.get_mut<Transform>()->position = Vec3::DOWN + Vec3::LEFT;
    entity4.get_mut<Transform>()->scale = Vec3::ONE * 0.1f;
    entity4.get_mut<Material>()->color = Color32::WHITE;*/
    
    ecs.system<Player, Transform, LinearKinematics>()
        .kind(stages->Update)
        .iter([this](flecs::iter& it, Player* players, Transform* transforms, LinearKinematics* linearKinematics)
        {
            float deltaTime = it.delta_time();

            flecs::world ecs = it.world();
            
            flecs::entity mainCameraEntity = ecs.singleton<MainCamera>();
            flecs::entity cameraEntity = mainCameraEntity.get<MainCamera>()->camera;
            Transform * const cameraTransform = cameraEntity.get_mut<Transform>();

            flecs::entity inputEntity = ecs.singleton<Input>();
            const Input* const input = inputEntity.get<Input>();

            for (auto i : it)
            {
                Player& player = players[i];
                Transform& transform = transforms[i];
                LinearKinematics& linear = linearKinematics[i];

                HandleInput(deltaTime, input, cameraTransform, player, transform, linear);
            }
        });
    
    ecs.system<Transform, Nametag>()
        .kind(stages->Draw)
        .iter([this](flecs::iter& it, Transform* transforms, Nametag* nametags)
        {
            float deltaTime = it.delta_time();

            flecs::world ecs = it.world();

            flecs::entity mainCameraEntity = ecs.singleton<MainCamera>();
            flecs::entity cameraEntity = mainCameraEntity.get<MainCamera>()->camera;
            const Transform * const cameraTransform = cameraEntity.get<Transform>();

            for (auto i : it)
            {
                Transform& transform = transforms[i];
                Nametag& linear = nametags[i];

                
            }
        }
    );
}

// Public Methods

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

// flecs::entity PlayerECSModule::CreatePlayerEntity
// (
//     const std::string& name,
//     const velecs::Vec3 position /* = velecs::Vec3::ZERO */,
//     const velecs::Vec3 rotation /* = velecs::Vec3::ZERO */
// )
// {
//     auto playerEntity = ECSManager::CreateEntity(ecs(), name, position, rotation);
//     playerEntity.set<Mesh>({})
//         .set<Material>({})
//         .set<LinearKinematics>({})
//         .set<AngularKinematics>({});

//     return playerEntity;
// }

void PlayerECSModule::HandleInput
(
    const float deltaTime,
    const Input* const input,
    Transform* const cameraTransform,
    Player& player,
    Transform& transform,
    LinearKinematics& linear
)
{
    Vec3 velDir = (((input->IsHeld(SDLK_d)) ? Vec3::RIGHT : Vec3::ZERO) +
        ((input->IsHeld(SDLK_a)) ? Vec3::LEFT : Vec3::ZERO) +
        ((input->IsHeld(SDLK_w)) ? Vec3::UP : Vec3::ZERO) +
        ((input->IsHeld(SDLK_s)) ? Vec3::DOWN : Vec3::ZERO)).Normalize();

    linear.velocity = 1.0f * (velDir);


    player.targetCamPos = player.targetCamPos + (input->mouseWheel.y * Vec3::BACKWARD);
    // Max and min are flipped and negative bc of the coordinate system
    player.targetCamPos.z = std::clamp(player.targetCamPos.z, -player.camMaxZoom, -player.camMinZoom);
    cameraTransform->position = Vec3::Lerp(cameraTransform->position, player.targetCamPos, player.camZoomSpeed * deltaTime);
}

} // namespace hh
