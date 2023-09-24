#pragma once
#include "Core.h"
#include "World/World.h"

#pragma warning(push, 0)  // Disable all warnings
#include <phmap/phmap.h>
#pragma warning(pop)

namespace DE
{
	class Engine
	{
	public:
		static void Init(); //Initialize engine
		static void Shutdown(); //Clean Shutdown

		static void BeginPlay();
		static void EndPlay();

		static void BeginFrame(); //Begin frame
		static void Update(f64 dt); //Update game
		static void Draw();
		static void EndFrame(); //End frame

		static World* CreateNewWorld();
		static World* LoadWorldFromFile(const char* fileName);

		static f64 GetDeltaTime() { return m_deltaTime; }
		static bool ShouldShutdown() { return m_ShouldShutdown; }
		static Object* GetObject(UID uid);
		static World* GetWorld() { return m_currentWorld; }
	private:
		static void Cleanup(); //Actual shutdown logic

		static void AddObject(Object* object); //For objects to add themselves
		static void RemoveObject(Object* object); //For objects to remove themselves

	private:
		static f64 m_deltaTime;
		static bool m_ShouldShutdown;

		static World* m_currentWorld;

		friend class Object;
		friend class App;
	};
}