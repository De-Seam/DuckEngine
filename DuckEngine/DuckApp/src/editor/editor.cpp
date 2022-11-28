#include "da/editor/editor.h"

#include "de/engine/engine.h"
#include "de/renderer/renderer.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_sdlrenderer.h"

#include <chrono>

namespace da
{
	bool Editor::m_is_running = false;
	f32 Editor::m_delta_time = F32_EPSILON;
	SDL_Texture* Editor::m_viewport_texture = nullptr;

	void Editor::init()
	{
		de::Engine::init();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		m_viewport_texture = SDL_CreateTexture(de::Renderer::get_renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1920, 1080);

		// Setup Platform/Renderer backends
		ImGui_ImplSDL2_InitForSDLRenderer(de::Renderer::get_window(), de::Renderer::get_renderer());
		ImGui_ImplSDLRenderer_Init(de::Renderer::get_renderer());

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

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
		}

		SDL_SetRenderTarget(de::Renderer::get_renderer(), m_viewport_texture);

		de::Engine::update(m_delta_time);

		ImGui::Begin("Window");
		ImGui::Text("Wow");
		ImGui::End();

		ImGui::Image((ImTextureID)m_viewport_texture, {1280, 720});


		SDL_SetRenderTarget(de::Renderer::get_renderer(), nullptr);
		ImGui::Render();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		de::Engine::end_frame();

		if(!de::Engine::get_is_running())
			m_is_running = false;
	}
}