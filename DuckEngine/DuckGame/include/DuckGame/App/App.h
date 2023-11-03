#pragma once
#include "DuckEngine/Core.h"

class App
{
public:
	static void Init();

private:
	static void MainLoop();
	static void Update(f32 dt);

private:
	static bool m_running;
	static f32 m_deltaTime;
};
