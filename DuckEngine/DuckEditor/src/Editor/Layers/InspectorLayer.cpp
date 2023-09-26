#include "Editor/Layers/InspectorLayer.h"
#include "Editor/Layers/ViewportLayer.h"
#include "Editor/Editor.h"

#include "Engine/Engine.h"
#include "World/World.h"
#include "DuckEngine/Resources/ResourceManager.h"
#include "DuckEngine/Resources/ResourceTypes/TextureResource.h"

#include <imgui/imgui_internal.h>
#include <imgui/imstb_textedit.h>

InspectorLayer::InspectorLayer()
{
}

#define IMGUI_VAR(func, label, code) ImGui::TextUnformatted(label); ImGui::NextColumn(); ImGui::SetNextItemWidth(-1); if(func) { code } ImGui::NextColumn();
#define IMGUI_VAR_IMG(func, label, code, img) ImGui::TextUnformatted(label); ImGui::NextColumn(); ImGui::SetNextItemWidth(-1); if(func) { code } ImGui::SameLine(); ImGui::NextColumn();

void InspectorLayer::Update(f32 dt)
{
	bool open = true;
	ImGui::Begin("Inspector##LayerWindow", &open);
	{
		m_context = ImGui::GetCurrentContext();

		if (!DE::Engine::GetWorld())
		{
			ImGui::End();
			return;
		}

		ViewportLayer* viewportLayer = Editor::GetLayer<ViewportLayer>();

		if (ImGui::BeginTabBar("InspectorTabBar"))
		{
			if (ImGui::BeginTabItem("Inspector"))
			{
				DE::Entity* selectedEntity = viewportLayer->GetSelectedEntity();
				if (selectedEntity)
				{
					ImGui::Columns(2);
					ImGui::SetColumnWidth(0, 64);

					//Create items to modify variables of the selected entity
					ImGui::Text(selectedEntity->GetName().c_str());
					ImGui::Separator();
					char entityNameBuffer[256];
					strcpy_s(entityNameBuffer, selectedEntity->GetName().c_str());

					static std::shared_ptr<DE::TextureResource> resourceTextureXButton = DE::ResourceManager::GetResource<DE::TextureResource>("Assets/Editor/Textures/XButtonIcon.png");
					static std::shared_ptr<DE::TextureResource> resourceTextureXYutton = DE::ResourceManager::GetResource<DE::TextureResource>("Assets/Editor/Textures/YButtonIcon.png");
					SDL_Texture* textureXButton = resourceTextureXButton->GetTexture();
					SDL_Texture* textureYButton = resourceTextureXYutton->GetTexture();
					
					IMGUI_VAR(ImGui::InputText("##NameInputText", entityNameBuffer, 256, ImGuiInputTextFlags_AlwaysInsertMode),
						"Name",
						selectedEntity->SetName(entityNameBuffer);
						);


					// Set a default item width for DragScalar
					const float defaultItemWidth = 100.0f;

					// Set a minimum width for DragScalar
					const float minDragWidth = 40.0f;


					ImGui::TextUnformatted("Position");
					ImGui::NextColumn();
					ImGui::Image(ImTextureID(textureXButton), ImVec2(19, 19), ImVec2(0, 0), ImVec2(1, 1));
					ImGui::SameLine(0.f, 0.f);

					// Calculate the available width for DragScalar
					const float availableWidth = ImGui::GetContentRegionAvail().x;
					const float dragWidth = std::max(minDragWidth, availableWidth * 0.5f); // Adjust the multiplier as needed
					
					ImGui::SetNextItemWidth(dragWidth);
					if (ImGui::DragScalar("##PositionInputX", ImGuiDataType_Double, &selectedEntity->m_position.x, 1, 0, 0, "%.3f"))
					{}
					ImGui::SameLine(0.f, 2.f);

					ImGui::Image(ImTextureID(textureYButton), ImVec2(19, 19), ImVec2(0, 0), ImVec2(1, 1));
					ImGui::SameLine(0.f, 0.f);

					ImGui::SetNextItemWidth(dragWidth);
					if (ImGui::DragScalar("##PositionInputY", ImGuiDataType_Double, &selectedEntity->m_position.y, 1, 0, 0, "%.3f"))
					{}

					ImGui::NextColumn();


					ImGui::TextUnformatted("Size");
					ImGui::NextColumn();
					ImGui::Image(ImTextureID(textureXButton), ImVec2(19, 19), ImVec2(0, 0), ImVec2(1, 1));
					ImGui::SameLine(0.f, 0.f);

					ImGui::SetNextItemWidth(dragWidth);
					if (ImGui::DragScalar("##SizeInputX", ImGuiDataType_Double, &selectedEntity->m_size.x, 1, 0, 0, "%.3f"))
					{}
					ImGui::SameLine(0.f, 2.f);

					ImGui::Image(ImTextureID(textureYButton), ImVec2(19, 19), ImVec2(0, 0), ImVec2(1, 1));
					ImGui::SameLine(0.f, 0.f);

					ImGui::SetNextItemWidth(dragWidth);
					if (ImGui::DragScalar("##SizeInputY", ImGuiDataType_Double, &selectedEntity->m_size.y, 1, 0, 0, "%.3f"))
					{}

					ImGui::NextColumn();

					IMGUI_VAR(ImGui::DragScalar("##RotationInput", ImGuiDataType_Double, &selectedEntity->m_rotation), "Rotation",
						{};);
				}
			}
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();

	if (!open)
		DestroyLayer();
}
