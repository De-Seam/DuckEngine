#include "App/App.h"

#include "DuckEditor/Editor.h"

#include "DuckEngine/Engine/Engine.h"
#include "DuckEngine/Resources/ResourceManager.h"
#include "DuckEngine/Renderer/Renderer.h"

#include <chrono>


bool App::m_running = false;
f64 App::m_deltaTime = F32_EPSILON;

void App::Init()
{
	DE::Engine::Init();

	EDITOR_ONLY(Editor::Init());

	//DE::World* world = DE::Engine::LoadWorldFromFile("Assets/World.json");

	DE::World* world = DE::Engine::CreateNewWorld();
	DE::Entity* entity = world->CreateEntity<DE::Entity>();
	entity->SetName("Test");
	entity->SetPosition(fm::vec2(10, 10));
	entity->SetSize(fm::vec2(100, 100));
	entity->SetRotation(30);
	const auto textureResource = DE::ResourceManager::GetResource<DE::TextureResource>("Assets/Textures/Player.png");
	entity->SetTexture(textureResource);

	entity = world->CreateEntity<DE::Entity>();
	entity->SetName("Test2");
	entity->SetPosition(fm::vec2(100, 100));
	entity->SetSize(fm::vec2(100, 100));
	entity->SetRotation(0);

	world->SaveToFile("Assets/World.json");

#ifndef DUCK_EDITOR
	DE::Engine::BeginPlay();
#endif

	MainLoop();

#ifndef DUCK_EDITOR
	DE::Engine::EndPlay();
#endif
}

void App::MainLoop()
{
	m_running = true;

	while (m_running)
	{
		auto start = std::chrono::steady_clock::now();

		Update(m_deltaTime);

		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<f64> elapsedChronoTime = end - start;
		m_deltaTime = elapsedChronoTime.count();
	}

	DE::Engine::Cleanup();
}

void App::Update(f64 dt)
{
	//DE::Engine::BeginFrame();

#ifdef DUCK_EDITOR
	Editor::Update(dt);
#else
	DE::Engine::BeginFrame();

	SDL_SetRenderDrawColor(DE::Renderer::GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(DE::Renderer::GetRenderer());

	DE::Engine::Update(dt);
	DE::Engine::Draw();

	DE::Engine::EndFrame();
#endif

	if (DE::Engine::ShouldShutdown())
	{
		m_running = false;
	}
	//DE::Engine::Update(m_deltaTime);

	//DE::Engine::EndFrame();
}