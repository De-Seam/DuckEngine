#include "da/editor/editor.h"
#include "da/editor/layers/viewport_layer.h"

#include "de/engine/engine.h"
#include "de/renderer/renderer.h"
#include "de/events/sdl_event_manager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_sdlrenderer.h"


#include <chrono>

namespace da
{
	bool Editor::m_is_running = false;
	f32 Editor::m_delta_time = F32_EPSILON;
	phmap::flat_hash_map<LayerType, Layer*> Editor::m_layers = {};
	SDL_Texture* Editor::m_viewport_texture = nullptr;

	void Editor::init()
	{
		de::Engine::init();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
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

		new ViewportLayer;

		main_loop();
	}

	SDL_Texture*& Editor::get_viewport_texture()
	{
		return m_viewport_texture;
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

		SDL_SetRenderDrawColor(de::Renderer::get_renderer(), 0, 0, 0, 255);
		SDL_RenderClear(de::Renderer::get_renderer());
		de::Engine::update(m_delta_time);

		for(auto& layer : m_layers)
			layer.second->update(dt);

		ImGui::ShowDemoWindow();

		SDL_SetRenderTarget(de::Renderer::get_renderer(), nullptr);
		ImGui::Render();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		de::Engine::end_frame();

		if(!de::Engine::get_is_running())
			m_is_running = false;
	}

	int Editor::add_layer(Layer* layer)
	{
		auto it = m_layers.find(layer->get_type());
		if(it != m_layers.end())
		{
			de::log(de::LogType::error, "Editor tried to add layer that already exists!");
			return 1; //Failure
		}
		m_layers[layer->get_type()] = layer;
		return 0; //Success
	}

	int Editor::delete_layer(Layer* layer)
	{
		if(m_layers.erase(layer->get_type()) == 0)
			return 1; //Failure
		return 0; //Success
	}
}