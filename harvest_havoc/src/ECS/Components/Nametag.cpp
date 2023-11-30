/// @file    Nametag.cpp
/// @author  Matthew Green
/// @date    2023-11-30 14:39:28
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "ECS/Components/Nametag.h"

using namespace velecs;

namespace hh {

// Public Fields

// Constructors and Destructors

Nametag::Nametag(const flecs::string_view& name)
    : name(std::string{name}){}

Nametag::Nametag(const std::string& name)
    : name(name) {}

// Public Methods

void Nametag::AddTo(flecs::world& ecs, flecs::entity entity)
{
    Vec3 offset = ((entity.get<Transform>()->scale.y * 0.5f) + 0.1f) * Vec3::UP;

    AddTo(ecs, entity, offset);
}

void Nametag::AddTo(flecs::world& ecs, flecs::entity entity, const Vec3 offset)
{
    flecs::entity nametagPrefab = CommonECSModule::GetPrefab(ecs, "hh::NametagECSModule::PR_Nametag");

    flecs::entity nametagEntity = ecs.entity()
        .is_a(nametagPrefab)
        .set<Nametag>({entity.name()})
        ;
    nametagEntity.set<Transform>({nametagEntity, offset});
    nametagEntity.child_of(entity);
}

void Nametag::Display
(
    const Transform& transform,
    const Transform* const cameraTransform,
    const PerspectiveCamera* const perspectiveCamera
) const
{
    Vec2 screenPos = transform.GetScreenPosition(cameraTransform, perspectiveCamera);
    ImVec2 windowPos = ImVec2(screenPos.x, screenPos.y);
    ImVec2 windowPivotPos = ImVec2(0.5f, 0.5f);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPivotPos);

    ImGuiWindowFlags windowFlags =
        ImGuiWindowFlags_NoDecoration
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoSavedSettings
        | ImGuiWindowFlags_NoFocusOnAppearing
        | ImGuiWindowFlags_NoNav
        | ImGuiWindowFlags_NoBackground
        ;

    const std::string windowName = name + " Nametag";
    ImGui::Begin(windowName.c_str(), nullptr, windowFlags);
    ImGui::Text(name.c_str());
    ImGui::End();
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace hh
