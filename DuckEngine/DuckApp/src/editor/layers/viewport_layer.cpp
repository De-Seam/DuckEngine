#include "da/editor/layers/viewport_layer.h"
#include "da/editor/editor.h"

#include "de/renderer/renderer.h"
#include "de/ecs/functions/render_collisions.h"
#include "de/entity/entity.h"
#include "de/ecs/components/gameplay_components.h"

namespace da
{
	ViewportLayer::ViewportLayer()
	{
		m_type = LayerType::Viewport;
	}

	void ViewportLayer::update(f32)
	{
		ImGui::Begin("ViewportWindow");
		{
			if(ImGui::Button("Play##ViewportPlayButton"))
				de::Engine::internal_begin_play();

			m_context = ImGui::GetCurrentContext();
			ImGui::BeginChild("ViewportGame", {0,0}, false, ImGuiWindowFlags_NoMove);
			{
				m_position = im_to_fm(ImGui::GetWindowPos());

				ImVec2 im_window_size = ImGui::GetWindowSize();
				ImGui::Image((ImTextureID)Editor::get_viewport_texture(), im_window_size);

				fm::vec2 window_size = im_to_fm(im_window_size);
				if(window_size.x != m_size.x || 
					window_size.y != m_size.y)
				{
					SDL_DestroyTexture(Editor::get_viewport_texture());
					Editor::get_viewport_texture() = SDL_CreateTexture(de::Renderer::get_renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, static_cast<int>(window_size.x), static_cast<int>(window_size.y));
					m_size = window_size;
				}


				if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				{
					ImVec2 im_mouse_pos = ImGui::GetMousePos();
					fm::vec2 mouse_pos = im_to_fm(ImGui::GetMousePos());
					m_selected_entity = de::get_entity_id_at_point(mouse_pos - m_position);

					de::log("%i", m_selected_entity);
				}

				if(m_selected_entity != entt::null)
				{
					if(ImGui::IsMouseDragging(ImGuiMouseButton_Left))
					{
						de::Entity* entity = de::Engine::get_world()->get_entity(m_selected_entity);
						de::PositionComponent& position_c = entity->get_component<de::PositionComponent>();
						fm::vec2 mouse_position = im_to_fm(ImGui::GetMousePos());
						position_c.position += (mouse_position - m_mouse_position);
					}
				}
			}
			ImGui::EndChild();
		}
		ImGui::End();

		m_mouse_position = im_to_fm(ImGui::GetMousePos());
	}
}