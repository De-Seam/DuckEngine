#include "Engine/Engine.h"
#include "Renderer/Renderer.h"
#include "Events/SDLEventManager.h"
#include "Events/InputManager.h"

namespace DE
{
	f64 Engine::m_deltaTime = 0.f;
	bool Engine::m_ShouldShutdown = false;
	World* Engine::m_currentWorld = nullptr;
	phmap::flat_hash_map<u64, Object*>* Engine::m_objects = nullptr;

	void Engine::Init()
	{
		Log(LogType::Message, "Initializing Engine");

		m_objects = new phmap::flat_hash_map<u64, Object*>();

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
	}

	void Engine::BeginFrame()
	{
		Renderer::BeginFrame();
	}

	void Engine::Update(f64 dt)
	{
		m_deltaTime = dt;

		SDLEventManager::Update();

		if (m_currentWorld)
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

	Object* Engine::GetObject(UID uid)
	{
		return (*m_objects)[uid];
	}

	void Engine::Cleanup()
	{
		Log(LogType::Message, "Cleanup Engine");

		Renderer::Shutdown();
		InputManager::Cleanup();

		delete m_objects;
		m_objects = nullptr;
	}

	void Engine::AddObject(Object* object)
	{
		Log(LogType::Message, "Adding Object %s", object->GetClassName());
		(*m_objects)[object->GetUID()] = object;
	}

	void Engine::RemoveObject(Object* object)
	{
		//If m_objects is nullptr the engine has already shut down
		if (!m_objects)
			return;
		Log(LogType::Message, "Removing Object %s", object->GetClassName());
		m_objects->erase(object->GetUID());
	}
}