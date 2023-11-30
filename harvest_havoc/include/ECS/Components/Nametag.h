/// @file    Nametag.h
/// @author  Matthew Green
/// @date    2023-11-22 17:34:41
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <string>

#include <imgui.h>

namespace velecs {

/// @struct Nametag
/// @brief Brief description.
///
/// Rest of description.
struct Nametag {
public:
    // Enums

    // Public Fields

    std::string name;

    // Constructors and Destructors

    /// @brief Default constructor.
    Nametag() = default;

    /// @brief Default deconstructor.
    ~Nametag() = default;

    // Public Methods

    static void AddTo(flecs::world& ecs, flecs::entity entity)
    {
        flecs::entity nametagPrefab = CommonECSModule::GetPrefab(ecs, "hh::PlayerECSModule::PR_Nametag");

        flecs::entity nametagEntity = ecs.entity()
            .is_a(nametagPrefab)
            ;
        
        Vec3 offset = ((entity.get<Transform>()->scale.y * 0.5f) + 0.1f) * Vec3::UP;

        nametagEntity.set<Transform>({nametagEntity, offset});
        nametagEntity.child_of(entity);
    }

    static void AddTo(flecs::world& ecs, flecs::entity entity, const Vec3 offset)
    {
        flecs::entity nametagPrefab = CommonECSModule::GetPrefab(ecs, "hh::PlayerECSModule::PR_Nametag");

        flecs::entity nametagEntity = ecs.entity()
            .is_a(nametagPrefab)
            ;
        nametagEntity.set<Transform>({nametagEntity, offset});
        nametagEntity.child_of(entity);
    }

    void Display
    (
        const Transform& transform,
        const Transform* const cameraTransform,
        const PerspectiveCamera* const perspectiveCamera,
        const float fontScale
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

        const std::string name = transform.GetParent().name();
        const std::string windowName = name + " Nametag";
        ImGui::Begin(windowName.c_str(), nullptr, windowFlags);
        ImGui::Text(name.c_str());
        ImGui::End();
    }

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
