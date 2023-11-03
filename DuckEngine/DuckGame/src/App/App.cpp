#include "App/App.h"

#include "DuckEditor/Editor.h"

#include "DuckEngine/Engine/Engine.h"
#include "DuckEngine/Resources/ResourceManager.h"
#include "DuckEngine/Renderer/Renderer.h"

#include <chrono>


bool App::m_running = false;
f32 App::m_deltaTime = F32_EPSILON;

void App::Init()
{
	DE::Engine::Init();

	EDITOR_ONLY(Editor::Init());

	DE::Engine::LoadWorldFromFile("Assets/Worlds/World.DuckWorld");

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
		std::chrono::duration<f32> elapsedChronoTime = end - start;
		m_deltaTime = elapsedChronoTime.count();
	}

	DE::Engine::Cleanup();
}

void App::Update(f32 dt)
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
