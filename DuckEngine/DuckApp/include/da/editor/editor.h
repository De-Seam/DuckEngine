#pragma once
#include "da/helper_functions.h"

#include "de/core.h"

#include "SDL/SDL.h"
#include "entt/entt.hpp"

namespace da
{
	class Editor
	{
	public:
		static void init();

	private:
		static void main_loop();
		static void update(f32 dt);

	private:
		static bool m_is_running;
		static f32 m_delta_time;

		static SDL_Texture* m_viewport_texture;
		static entt::entity m_selected_entity;
		static fm::vec2 m_viewport_position;
		static fm::vec2 m_viewport_size;
	};
}