#include "Editor/Layers/OutlinerLayer.h"
#include "Editor/Layers/ViewportLayer.h"
#include "Editor/Editor.h"

#include "Engine/Engine.h"
#include "World/World.h"

OutlinerLayer::OutlinerLayer()
{
}

void OutlinerLayer::Update(f32 dt)
{
    bool open = true;
    ImGui::Begin("OutlinerLayerWindow", &open);
    {
        m_context = ImGui::GetCurrentContext();

        if (!DE::Engine::GetWorld())
        {
            ImGui::End();
            return;
        }

        ViewportLayer* viewportLayer = Editor::GetLayer<ViewportLayer>();

        if (ImGui::BeginTabBar("OutlinerTabBar"))
        {
            if (ImGui::BeginTabItem("Inspector"))
            {
                DE::World* world = DE::Engine::GetWorld();
                const std::vector<std::unique_ptr<DE::Entity>>& entities = world->GetEntities();

                // Create a scrollable region for the Inspector tab
                ImGui::BeginChild("InspectorScroll", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
                {
                    for (u_size i = 0; i < entities.size(); i++)
                    {
                        const std::unique_ptr<DE::Entity>& entity = entities[i];

                        if (ImGui::Button((entity.get()->GetName() + std::to_string(i)).c_str()))
                        {
                            viewportLayer->SetSelectedEntity(entity.get());
                        }
                    }

                }
                ImGui::EndChild();
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();

        if (ImGui::BeginTabBar("InspectorTabBar"))
        {
            if (ImGui::BeginTabItem("Entity Inspector"))
            {

            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();

    if (!open)
        DestroyLayer();
}
