#ifdef DUCK_EDITOR

#include "DuckEditor/Editor.h"
#include "DuckEditor/Layers/MainMenuBarLayer.h"
#include "DuckEditor/Layers/ViewportLayer.h"
#include "DuckEditor/Layers/OutlinerLayer.h"
#include "DuckEditor/Layers/InspectorLayer.h"

#include "DuckEngine/Engine/Engine.h"
#include "DuckEngine/Renderer/Renderer.h"
#include "DuckEngine/Events/SDLEventManager.h"
#include "DuckEngine/World/World.h"
#include "DuckEngine/Resources/ResourceManager.h"
#include "DuckEngine/Resources/ResourceTypes/TextureResource.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_sdlrenderer.h"


#include <chrono>

phmap::flat_hash_map<LayerType, std::unique_ptr<Layer>> Editor::m_layers = {};
SDL_Texture* Editor::m_viewportTexture = nullptr;
ImGuiID Editor::m_dockID = 0;

void Editor::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	m_viewportTexture = SDL_CreateTexture(DE::Renderer::GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
										SDL_TEXTUREACCESS_TARGET, 1920, 1080);

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(DE::Renderer::GetWindow(), DE::Renderer::GetRenderer());
	ImGui_ImplSDLRenderer_Init(DE::Renderer::GetRenderer());

	DE::SDLEventFunction sdl_imgui_event_function;
	sdl_imgui_event_function.function_ptr =
	{
		[](SDL_Event& e)
		{
			ImGui_ImplSDL2_ProcessEvent(&e);
		}
	};
	DE::SDLEventManager::AddEventFunction(sdl_imgui_event_function, true);

	CreateLayer<MainMenuBarLayer>();
	CreateLayer<ViewportLayer>();
	CreateLayer<OutlinerLayer>();
	CreateLayer<InspectorLayer>();
}

void Editor::ResizeViewport(fm::ivec2 newSize)
{
	SDL_DestroyTexture(m_viewportTexture);
	m_viewportTexture = SDL_CreateTexture(DE::Renderer::GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
										SDL_TEXTUREACCESS_TARGET, newSize.x, newSize.y);

	DE::Renderer::m_windowSize = newSize;
}

SDL_Texture* Editor::GetViewportTexture()
{
	return m_viewportTexture;
}

void Editor::Update(f32 dt)
{
	DE::Engine::BeginFrame();
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	m_dockID = ImGui::DockSpaceOverViewport();

	SDL_SetRenderTarget(DE::Renderer::GetRenderer(), m_viewportTexture);

	SDL_SetRenderDrawColor(DE::Renderer::GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(DE::Renderer::GetRenderer());

	DE::Engine::Update(dt);
	DE::Engine::Draw();

	for (auto& layer : m_layers)
		layer.second->Update(dt);

	//ImGui::ShowDemoWindow();

	SDL_SetRenderTarget(DE::Renderer::GetRenderer(), nullptr);
	ImGui::Render();
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();

	DE::Engine::EndFrame();
}

#define ENUM_TO_STRING(x) #x

void Editor::DestroyLayer(LayerType layerType)
{
	Log(DE::LogType::Info, "Destroying Layer %s", ENUM_TO_STRING(layerType));

	if (m_layers.find(layerType) != m_layers.end())
	{
		m_layers.erase(layerType);
	}
	else
	{
		Log(DE::LogType::Error, "LayerType not found");
	}
}

#endif
