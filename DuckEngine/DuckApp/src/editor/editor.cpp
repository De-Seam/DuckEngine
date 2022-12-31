#include "da/editor/editor.h"

#include "de/engine/engine.h"
#include "de/renderer/renderer.h"
#include "de/events/sdl_event_manager.h"
#include "de/ecs/functions/render_collisions.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_sdlrenderer.h"


#include <chrono>

namespace da
{
	bool Editor::m_is_running = false;
	f32 Editor::m_delta_time = F32_EPSILON;
	SDL_Texture* Editor::m_viewport_texture = nullptr;
	entt::entity Editor::m_selected_entity = entt::null;
	fm::vec2 Editor::m_viewport_position = {0.f,0.f};
	fm::vec2 Editor::m_viewport_size = {0.f,0.f};

	void Editor::init()
	{
		de::Engine::init();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		m_viewport_texture = SDL_CreateTexture(de::Renderer::get_renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1920, 1080);

		// Setup Platform/Renderer backends
		ImGui_ImplSDL2_InitForSDLRenderer(de::Renderer::get_window(), de::Renderer::get_renderer());
		ImGui_ImplSDLRenderer_Init(de::Renderer::get_renderer());

		de::SDLEventFunction sdl_imgui_event_function;
		sdl_imgui_event_function.function_ptr = 
		{[](SDL_Event& e)
		{
			ImGui_ImplSDL2_ProcessEvent(&e);
		}};
		de::SDLEventManager::add_event_function(sdl_imgui_event_function, true);

		main_loop();
	}

	void Editor::main_loop()
	{
		m_is_running = true;
		auto current_time = std::chrono::steady_clock::now();

		while(m_is_running)
		{
			auto start = std::chrono::steady_clock::now();

			update(m_delta_time);

			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<f32> elapsed_chrono_time = end - start;
			m_delta_time = elapsed_chrono_time.count();
		}

		de::Engine::shutdown();
	}

	void Editor::update(f32 dt)
	{
		de::Engine::begin_frame();
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		ImGuiID m_dock_id = ImGui::DockSpaceOverViewport();

		SDL_SetRenderTarget(de::Renderer::get_renderer(), m_viewport_texture);

		de::Engine::update(m_delta_time);

		ImGui::Begin("ViewportWindow");
		{

			ImGui::BeginChild("ViewportGame");
			{
				m_viewport_position = im_to_fm(ImGui::GetWindowPos());

				ImVec2 im_window_size = ImGui::GetWindowSize();
				ImGui::Image((ImTextureID)m_viewport_texture, im_window_size);

				fm::vec2 window_size = im_to_fm(im_window_size);
				if(window_size.x != m_viewport_size.x || 
					window_size.y != m_viewport_size.y)
				{
					SDL_DestroyTexture(m_viewport_texture);
					m_viewport_texture = SDL_CreateTexture(de::Renderer::get_renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, static_cast<int>(window_size.x), static_cast<int>(window_size.y));
					m_viewport_size = window_size;
				}


				if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				{
					ImVec2 im_mouse_pos = ImGui::GetMousePos();
					fm::vec2 mouse_pos = im_to_fm(ImGui::GetMousePos());
					m_selected_entity = de::get_entity_id_at_point(mouse_pos - m_viewport_position);

					de::log("%i", m_selected_entity);
				}
			}
			ImGui::EndChild();
		}
		ImGui::End();

		ImGui::ShowDemoWindow();

		SDL_SetRenderTarget(de::Renderer::get_renderer(), nullptr);
		ImGui::Render();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		de::Engine::end_frame();

		if(!de::Engine::get_is_running())
			m_is_running = false;
	}
}