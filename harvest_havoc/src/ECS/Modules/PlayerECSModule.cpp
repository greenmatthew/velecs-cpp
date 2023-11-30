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

#include <imgui.h>

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
    ecs.import<NametagECSModule>();

    // CreatePlayerEntity("Player");

    flecs::entity renderingECSModule = ecs.lookup("velecs::RenderingECSModule");
    const Rect extent = renderingECSModule.get<RenderingECSModule>()->GetWindowExtent();
    
    flecs::entity cameraEntity = RenderingECSModule::CreatePerspectiveCamera(ecs, Vec3{0.0f, 0.0f, -2.0f}, Vec3{0.0f, 0.0f, 0.0f}, extent.max.x / extent.max.y);

    ecs.set<MainCamera>({cameraEntity, extent});

    flecs::entity trianglePrefab = CommonECSModule::GetPrefab(ecs, "velecs::RenderingECSModule::PR_TriangleRender");
    flecs::entity squarePrefab = CommonECSModule::GetPrefab(ecs, "velecs::RenderingECSModule::PR_SquareRender");
    flecs::entity player = ecs.entity("Player")
        .is_a(trianglePrefab)
        .add<Player>()
        .add<LinearKinematics>()
        .add<AngularKinematics>()
        ;
    player.get_mut<Transform>()->entity = player;
    player.get_mut<Material>()->color = Color32::GREEN;
    // player.set_override<SimpleMesh>({SimpleMesh::MONKEY()});
    
    cameraEntity.child_of(player);

    Nametag::AddTo(ecs, player);

    flecs::entity entity1 = ecs.entity()
        .is_a(trianglePrefab)
        .set_name("Entity1")
        ;
    entity1.get_mut<Transform>()->entity = entity1;
    entity1.get_mut<Transform>()->position = Vec3::UP + Vec3::RIGHT;
    entity1.get_mut<Transform>()->scale = Vec3::ONE * 0.1f;
    Nametag::AddTo(ecs, entity1);

    flecs::entity entity2 = ecs.entity()
        .is_a(squarePrefab)
        .set_name("Entity2")
        ;
    entity2.get_mut<Transform>()->entity = entity2;
    entity2.get_mut<Transform>()->position = Vec3::UP + Vec3::LEFT;
    entity2.get_mut<Transform>()->scale = Vec3::ONE * 0.1f;
    entity2.get_mut<Material>()->color = Color32::YELLOW;
    Nametag::AddTo(ecs, entity2);

    flecs::entity entity3 = ecs.entity()
        .is_a(squarePrefab)
        .set_name("Entity3")
        ;
    entity3.get_mut<Transform>()->entity = entity3;
    entity3.get_mut<Transform>()->position = Vec3::DOWN + Vec3::RIGHT;
    entity3.get_mut<Transform>()->scale = Vec3::ONE * 0.1f;
    entity3.get_mut<Material>()->color = Color32::ORANGE;
    Nametag::AddTo(ecs, entity3);
    
    flecs::entity entity4 = ecs.entity()
        .is_a(squarePrefab)
        .set_name("Entity4")
        ;
    entity4.get_mut<Transform>()->entity = entity4;
    entity4.get_mut<Transform>()->position = Vec3::DOWN + Vec3::LEFT;
    entity4.get_mut<Transform>()->scale = Vec3::ONE * 0.1f;
    entity4.get_mut<Material>()->color = Color32::WHITE;
    Nametag::AddTo(ecs, entity4);

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

    linear.velocity = player.baseMovementSpeed * (velDir);


    player.targetCamPos = Vec3
    (
        cameraTransform->position.x,
        cameraTransform->position.y,
        std::clamp(player.targetCamPos.z - input->mouseWheel.y, -player.camMaxZoom, -player.camMinZoom)
    );
    // Max and min are flipped and negative bc of the coordinate system
    cameraTransform->position = Vec3::Lerp(cameraTransform->position, player.targetCamPos, player.camZoomSpeed * deltaTime);

    if (input->IsPressed(SDLK_KP_PLUS))
    {
        cameraTransform->rotation.x += -5.0f;
        std::cout << cameraTransform->rotation << std::endl;
    }

    if (input->IsPressed(SDLK_KP_MINUS))
    {
        cameraTransform->rotation.x += 5.0f;
        std::cout << cameraTransform->rotation << std::endl;
    }


    if (input->IsPressed(SDLK_RIGHT))
    {
        cameraTransform->position -= Vec3::RIGHT * 0.25f;
        std::cout << "pressed right arrow key" << std::endl;
        std::cout << "new cam pos: " << cameraTransform->position << std::endl;
        std::cout << "new cam abs pos: " << cameraTransform->GetAbsPosition() << '\n' << std::endl;
    }
    if (input->IsPressed(SDLK_LEFT))
    {
        cameraTransform->position -= Vec3::LEFT * 0.25f;
        std::cout << "pressed left arrow key" << std::endl;
        std::cout << "new cam pos: " << cameraTransform->position << std::endl;
        std::cout << "new cam abs pos: " << cameraTransform->GetAbsPosition() << '\n' << std::endl;
    }
    if (input->IsPressed(SDLK_UP))
    {
        cameraTransform->position -= Vec3::UP * 0.25f;
        std::cout << "pressed up arrow key" << std::endl;
        std::cout << "new cam pos: " << cameraTransform->position << std::endl;
        std::cout << "new cam abs pos: " << cameraTransform->GetAbsPosition() << '\n' << std::endl;
    }
    if (input->IsPressed(SDLK_DOWN))
    {
        cameraTransform->position -= Vec3::DOWN * 0.25f;
        std::cout << "pressed down arrow key" << std::endl;
        std::cout << "new cam pos: " << cameraTransform->position << std::endl;
        std::cout << "new cam abs pos: " << cameraTransform->GetAbsPosition() << '\n' << std::endl;
    }
}

} // namespace hh
