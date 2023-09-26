#include "Editor/Layers/InspectorLayer.h"
#include "Editor/Layers/ViewportLayer.h"
#include "Editor/Editor.h"

#include "Engine/Engine.h"
#include "World/World.h"

#include <imgui/imgui_internal.h>
#include <imgui/imstb_textedit.h>

InspectorLayer::InspectorLayer()
{
}

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

					//Create items to modify variables of the selected entity
					ImGui::Text(selectedEntity->GetName().c_str());
					ImGui::Separator();
					char entityNameBuffer[256];
					strcpy_s(entityNameBuffer, selectedEntity->GetName().c_str());
					
					IMGUI_VAR(ImGui::InputText("##NameInputText", entityNameBuffer, 256, ImGuiInputTextFlags_AlwaysInsertMode), "Name",
						selectedEntity->SetName(entityNameBuffer);
						);

					ImGui::Text("Position:");
					ImGui::SameLine(); // Align the X image to the right of the label
					//ImGui::Image((ImTextureID)yourXImageTexture, ImVec2(16, 16)); // Replace 'yourXImageTexture' with your actual texture

					// Drag for X
					ImGui::SameLine(); // Align the X input to the right of the X image
					ImGui::DragScalar("##XPositionInput", ImGuiDataType_Double, &selectedEntity->m_position.x, 1.0f);

					ImGui::SameLine(); // Align the Y image to the right of the X input
					//ImGui::Image((ImTextureID)yourYImageTexture, ImVec2(16, 16)); // Replace 'yourYImageTexture' with your actual texture

					// Drag for Y
					ImGui::SameLine(); // Align the Y input to the right of the Y image
					ImGui::DragScalar("##YPositionInput", ImGuiDataType_Double, &selectedEntity->m_position.y, 1.0f);

					IMGUI_VAR(ImGui::DragScalarN("##PositionInput", ImGuiDataType_Double, &selectedEntity->m_position.x, 2), "Position",
						{};);

					IMGUI_VAR(ImGui::DragScalarN("##SizeInput", ImGuiDataType_Double, &selectedEntity->m_size.x, 2), "Size",
						{};);

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
