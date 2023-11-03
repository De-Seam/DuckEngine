#ifdef DUCK_EDITOR

#include "DuckEditor/Layers/OutlinerLayer.h"
#include "DuckEditor/Layers/ViewportLayer.h"
#include "DuckEditor/Editor.h"

#include "Engine/Engine.h"
#include "World/World.h"

OutlinerLayer::OutlinerLayer()
{}

void OutlinerLayer::Update(f64)
{
	bool open = true;
	ImGui::Begin("Outliner##LayerWindow", &open);
	{
		m_context = ImGui::GetCurrentContext();

		if (!DE::Engine::GetWorld())
		{
			ImGui::End();
			return;
		}

		ViewportLayer* viewportLayer = Editor::GetLayer<ViewportLayer>();
		std::shared_ptr<DE::Entity> selectedEntity = viewportLayer->GetSelectedEntity().lock();

		if (ImGui::BeginTabBar("OutlinerTabBar"))
		{
			if (ImGui::BeginTabItem("Outliner"))
			{
				DE::World* world = DE::Engine::GetWorld();
				const std::vector<std::shared_ptr<DE::Entity>>& entities = world->GetEntities();

				// Create a scrollable region for the Inspector tab
				ImGui::BeginChild("OutlinerScroll", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false,
								ImGuiWindowFlags_HorizontalScrollbar);
				{
					for (u_size i = 0; i < entities.size(); i++)
					{
						const std::shared_ptr<DE::Entity>& entity = entities[i];

						if (entity == selectedEntity)
							ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
						else
							ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));

						if (ImGui::Button((entity->GetName() + "##" + std::to_string(i)).c_str(),
										ImVec2(ImGui::GetContentRegionAvail().x, 0)))
						{
							viewportLayer->SetSelectedEntity(entity);
						}

						ImGui::PopStyleColor();
					}
				}
				ImGui::EndChild();
			}
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();

	if (!open)
		DestroyLayer();
}


#endif
