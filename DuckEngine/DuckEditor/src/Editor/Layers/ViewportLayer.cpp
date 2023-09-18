#include "Editor/Layers/ViewportLayer.h"
#include "Editor/Editor.h"

#include "Engine/Engine.h"
#include "Renderer/Renderer.h"

//#include "renderer/renderer.h"
//#include "ecs/functions/render_collisions.h"
//#include "entity/entity.h"
//#include "ecs/components/gameplay_components.h"

ViewportLayer::ViewportLayer()
{
	m_type = LayerType::Viewport;
}

void ViewportLayer::update(f32)
{
	ImGui::Begin("ViewportWindow");
	{
		//if (ImGui::Button("Play##ViewportPlayButton"))
		//	de::Engine::internal_begin_play();

		m_context = ImGui::GetCurrentContext();
		ImGui::BeginChild("ViewportGame", { 0,0 }, false, ImGuiWindowFlags_NoMove);
		{
			m_position = IMToFM(ImGui::GetWindowPos());

			ImVec2 im_window_size = ImGui::GetWindowSize();
			ImGui::Image((ImTextureID)Editor::GetViewportTexture(), im_window_size);

			fm::vec2 window_size = IMToFM(im_window_size);
			if (window_size.x != m_size.x ||
				window_size.y != m_size.y)
			{
				SDL_DestroyTexture(Editor::GetViewportTexture());
				Editor::GetViewportTexture() = SDL_CreateTexture(DE::Renderer::GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, static_cast<int>(window_size.x), static_cast<int>(window_size.y));
				m_size = window_size;
			}


			//if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
			//{
			//	if (DE::Engine::get_world())
			//	{
			//		ImVec2 im_mouse_pos = ImGui::GetMousePos();
			//		fm::vec2 mouse_pos = IMToFM(ImGui::GetMousePos());
			//		m_selected_entity = DE::GetEntityIDAtPoint(mouse_pos - m_position);
			//
			//		DE::Log("%i", m_selected_entity);
			//	}
			//}
			//
			//if (m_selected_entity != entt::null)
			//{
			//	if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
			//	{
			//		DE::Entity* entity = DE::Engine::get_world()->get_entity(m_selected_entity);
			//		DE::PositionComponent& position_c = entity->get_component<DE::PositionComponent>();
			//		fm::vec2 mouse_position = IMToFM(ImGui::GetMousePos());
			//		position_c.position += (mouse_position - m_mouse_position);
			//	}
			//}
		}
		ImGui::EndChild();
	}
	ImGui::End();

	m_mouse_position = IMToFM(ImGui::GetMousePos());
}