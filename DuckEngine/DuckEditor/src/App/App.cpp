#include "App/App.h"
#include "Editor/Editor.h"

#include "DuckEngine/Engine/Engine.h"

#include <chrono>

bool App::m_running = false;
f64 App::m_deltaTime = F32_EPSILON;

void App::Init()
{
	DE::Engine::Init();
	Editor::Init();

	//DE::World* world = DE::Engine::LoadWorldFromFile("Assets/World.json");

	DE::World* world = DE::Engine::CreateNewWorld();
	DE::Entity* entity = world->CreateEntity<DE::Entity>();
	entity->name = "Test";
	entity->position = fm::vec2(10, 10);
	entity->size = fm::vec2(1, 1);
	entity->rotation = 0;

	entity = world->CreateEntity<DE::Entity>();
	entity->name = "Test2";
	entity->position = fm::vec2(10, 10);
	entity->size = fm::vec2(1, 1);
	entity->rotation = 0;
	
	world->SaveToFile("Assets/World.json");

	MainLoop();
}

void App::MainLoop()
{
	m_running = true;
	auto current_time = std::chrono::steady_clock::now();

	while (m_running)
	{
		auto start = std::chrono::steady_clock::now();

		Update(m_deltaTime);

		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<f64> elapsed_chrono_time = end - start;
		m_deltaTime = elapsed_chrono_time.count();
	}

	DE::Engine::Cleanup();
}

void App::Update(f64 dt)
{
	//DE::Engine::BeginFrame();

	Editor::Update(dt);

	if (DE::Engine::ShouldShutdown())
	{
		m_running = false;
	}
	//DE::Engine::Update(m_deltaTime);

	//DE::Engine::EndFrame();
}