#ifdef DUCK_EDITOR

#include "DuckEditor/Layers/ViewportLayer.h"
#include "DuckEditor/Editor.h"
#include "DuckEditor/Layers/InspectorLayer.h"

#include "DuckEngine/Engine/Engine.h"
#include "DuckEngine/Renderer/Renderer.h"

ViewportLayer::ViewportLayer()
{}

void ViewportLayer::Update(f64)
{
	ImGui::Begin("Viewport##LayerWindow");
	{
		m_context = ImGui::GetCurrentContext();

		if (ImGui::Button("Play##ViewportPlayButton"))
			DE::Engine::BeginPlay();

		ImGui::BeginChild("ViewportGame", {0, 0}, false, ImGuiWindowFlags_NoMove);
		{
			m_position = IMToFM(ImGui::GetWindowPos());

			ImVec2 im_window_size = ImGui::GetWindowSize();
			ImGui::Image(Editor::GetViewportTexture(), im_window_size);

			fm::vec2 window_size = IMToFM(im_window_size);
			if (window_size.x != m_size.x ||
				window_size.y != m_size.y)
			{
				SDL_DestroyTexture(Editor::GetViewportTexture());
				Editor::GetViewportTexture() = SDL_CreateTexture(DE::Renderer::GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
																SDL_TEXTUREACCESS_TARGET,
																static_cast<int>(window_size.x),
																static_cast<int>(window_size.y));
				m_size = window_size;
			}


			if (ImGui::IsWindowHovered())
			{
				if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				{
					if (DE::Engine::GetWorld())
					{
						const fm::vec2 mousePosition = IMToFM(ImGui::GetMousePos());
						m_selectedEntity = DE::Renderer::GetEntityAtPointSlow(mousePosition - m_position);

						if (m_selectedEntity)
							DE::Log("Selected Entity: %s", m_selectedEntity->GetName().c_str());
					}
				}

				if (m_selectedEntity != nullptr)
				{
					if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
					{
						const fm::vec2 mousePosition = IMToFM(ImGui::GetMousePos());
						m_selectedEntity->SetPosition(
							m_selectedEntity->GetPosition() + (mousePosition - m_mouse_position));
					}
				}
			}
		}
		ImGui::EndChild();
	}
	ImGui::End();

	m_mouse_position = IMToFM(ImGui::GetMousePos());
}

void ViewportLayer::SetSelectedEntity(DE::Entity* entity)
{
	Log(DE::LogType::Info, "Selected entity %s", entity->GetName().c_str());
	m_selectedEntity = entity;

	if (!Editor::LayerExists<InspectorLayer>())
		Editor::CreateLayer<InspectorLayer>();
}

#endif
