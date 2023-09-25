#include "Engine/Engine.h"
#include "Renderer/Renderer.h"
#include "Events/SDLEventManager.h"
#include "Events/InputManager.h"

namespace DE
{
	f64 Engine::m_deltaTime = 0.f;
	bool Engine::m_ShouldShutdown = false;
	bool Engine::m_playing = false;
	World* Engine::m_currentWorld = nullptr;

	static phmap::flat_hash_map<u64, Object*> g_objects = {};

	void Engine::Init()
	{
		Log(LogType::Message, "Initializing Engine");

		Renderer::Init();
		InputManager::Init();

		DE::SDLEventFunction shutdownFunc;
		shutdownFunc.event_type = SDL_QUIT;
		shutdownFunc.function_ptr =
			[](const SDL_Event& event)
		{
			if (event.type == SDL_QUIT)
			{
				Engine::Shutdown();
			}
		};
		SDLEventManager::AddEventFunction(shutdownFunc, false);
	}

	void Engine::Shutdown()
	{
		Log(LogType::Message, "Engine Shutdown called");
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
		m_currentWorld = new World();
		return m_currentWorld;
	}

	World* Engine::LoadWorldFromFile(const char* fileName)
	{
		if (m_currentWorld)
		{
			m_currentWorld->EndPlay();
			delete m_currentWorld;
		}
		m_currentWorld = new World();
		m_currentWorld->LoadFromFile(fileName);
		if (m_playing)
			m_currentWorld->BeginPlay();
		return m_currentWorld;
	}

	Object* Engine::GetObject(UID uid)
	{
		return g_objects[uid];
	}

	void Engine::Cleanup()
	{
		Log(LogType::Message, "Cleanup Engine");

		Renderer::Shutdown();
		InputManager::Cleanup();
	}

	void Engine::AddObject(Object* object)
	{
		Log(LogType::Message, "Adding Object %s", object->GetClassName());
		g_objects[object->GetUID()] = object;
	}

	void Engine::RemoveObject(Object* object)
	{
		Log(LogType::Message, "Removing Object %s", object->GetClassName());
		g_objects.erase(object->GetUID());
	}
}