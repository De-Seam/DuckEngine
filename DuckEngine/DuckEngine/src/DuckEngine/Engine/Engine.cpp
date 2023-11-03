#include "Engine/Engine.h"

#include "Engine/LogManager.h"
#include "Renderer/Renderer.h"
#include "Events/SDLEventManager.h"
#include "Events/InputManager.h"

namespace DE
{
f64 Engine::m_deltaTime = 0.f;
bool Engine::m_ShouldShutdown = false;
bool Engine::m_playing = false;
std::unique_ptr<World> Engine::m_currentWorld = nullptr;
phmap::flat_hash_map<u64, Object*> Engine::m_objects = {};

void Engine::Init()
{
	LogManager::Init();

	Log(LogType::Info, "Initializing Engine");

	Renderer::Init();
	InputManager::Init();

	SDLEventFunction shutdownFunc;
	shutdownFunc.event_type = SDL_QUIT;
	shutdownFunc.function_ptr =
		[](const SDL_Event&)
		{
			Shutdown();
		};
	SDLEventManager::AddEventFunction(shutdownFunc, false);
}

void Engine::Shutdown()
{
	Log(LogType::Info, "Engine Shutdown called");
	m_ShouldShutdown = true;
}

void Engine::BeginPlay()
{
	m_playing = true;

	if (m_currentWorld)
	{
		m_currentWorld->BeginPlay();
	}
}

void Engine::EndPlay()
{
	if (m_currentWorld)
	{
		m_currentWorld->EndPlay();
	}

	m_playing = false;
}

void Engine::BeginFrame()
{
	Renderer::BeginFrame();
}

void Engine::Update(f64 dt)
{
	m_deltaTime = dt;

	SDLEventManager::Update();
	Renderer::Update(dt);

	if (m_currentWorld && m_playing)
	{
		m_currentWorld->Update(dt);
	}
}

void Engine::Draw()
{
	if (m_currentWorld)
	{
		m_currentWorld->Draw();
	}
}

void Engine::EndFrame()
{
	Renderer::EndFrame();
}

World* Engine::CreateNewWorld()
{
	m_currentWorld = std::make_unique<World>();
	return m_currentWorld.get();
}

World* Engine::LoadWorldFromFile(const char* fileName)
{
	if (m_currentWorld)
	{
		m_currentWorld->EndPlay();
	}
	World* world = CreateNewWorld();
	world->LoadFromFile(fileName);
	if (m_playing)
		world->BeginPlay();
	return world;
}

Object* Engine::GetObject(UID uid)
{
	return m_objects[uid];
}

void Engine::Cleanup()
{
	Log(LogType::Info, "Cleanup Engine");

	Renderer::Shutdown();
	InputManager::Cleanup();

	LogManager::Cleanup();
}

void Engine::AddObject(Object* object)
{
	Log(LogType::Info, "Adding Object %s", object->GetClassName());
	m_objects[object->GetUID()] = object;
}

void Engine::RemoveObject(Object* object)
{
	Log(LogType::Info, "Removing Object %s", object->GetClassName());
	m_objects.erase(object->GetUID());
}
}
