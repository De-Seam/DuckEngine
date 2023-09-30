#ifdef DUCK_EDITOR

#include "DuckEditor/Layers/InspectorLayer.h"
#include "DuckEditor/Layers/ViewportLayer.h"
#include "DuckEditor/Editor.h"

#include "Engine/Engine.h"
#include "World/World.h"
#include "DuckEngine/Resources/ResourceManager.h"
#include "DuckEngine/Resources/ResourceTypes/TextureResource.h"

#include <imgui/imgui_internal.h>
#include <imgui/imstb_textedit.h>

InspectorLayer::InspectorLayer()
{
	const std::shared_ptr<DE::TextureResource> resourceTextureXButton =
		DE::ResourceManager::GetResource<DE::TextureResource>("Assets/Editor/Textures/XButtonIcon.png");
	const std::shared_ptr<DE::TextureResource> resourceTextureYButton =
		DE::ResourceManager::GetResource<DE::TextureResource>("Assets/Editor/Textures/YButtonIcon.png");

	m_positionColum.text = "Position";
	m_positionColum.perScalarData =
	{
		ColumnDragScalar::PerScalarData{"##PositionX", resourceTextureXButton},
		ColumnDragScalar::PerScalarData{"##PositionY", resourceTextureYButton}
	};

	m_sizeColum.text = "Size";
	m_sizeColum.perScalarData =
	{
		ColumnDragScalar::PerScalarData{"##SizeX", resourceTextureXButton},
		ColumnDragScalar::PerScalarData{"##SizeY", resourceTextureYButton}
	};

	m_rotationColum.text = "Rotation";
	m_rotationColum.perScalarData =
	{
		ColumnDragScalar::PerScalarData{"##Rotation", nullptr}
	};
}

#define IMGUI_VAR(func, label, code) ImGui::TextUnformatted(label); ImGui::NextColumn(); ImGui::SetNextItemWidth(-1); if(func) { code } ImGui::NextColumn();

void InspectorLayer::Update(f64)
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

					IMGUI_VAR(
						ImGui::InputText("##NameInputText", entityNameBuffer, 256, ImGuiInputTextFlags_AlwaysInsertMode
						),
						"Name",
						selectedEntity->SetName(entityNameBuffer);
					);

					void* positionData[2] = {&selectedEntity->m_position.x, &selectedEntity->m_position.y};
					m_positionColum.Update(positionData);
					void* sizeData[2] = {&selectedEntity->m_size.x, &selectedEntity->m_size.y};
					m_sizeColum.Update(sizeData);
					void* rotationData[1] = {&selectedEntity->m_rotation};
					m_rotationColum.Update(rotationData);
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

#endif
