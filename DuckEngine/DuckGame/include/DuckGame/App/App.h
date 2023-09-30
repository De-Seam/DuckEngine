#pragma once
#include "DuckEngine/Core.h"

class App
{
public:
	static void Init();

private:
	static void MainLoop();
	static void Update(f64 dt);

private:
	static bool m_running;
	static f64 m_deltaTime;
};