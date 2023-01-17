#pragma once
#include "de/core.h"

#include <SDL/SDL.h>
#include <phmap/phmap.h>

#include <functional>
#include <map>

namespace de //DuckEngine
{
	enum class Key : u_size
	{
		A = 0,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		ONE,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		ZERO,
		FORWARDSLASH,
		BACKSLASH,
		SMALLER,
		BIGGER,
		DOT,
		COMMA,
		SHIFT,
		CONTROL,
		CAPSLOCK,
		TAB,
		LEFTALT,
		RIGHTALT,

		LAST //Last item
	};

	enum class MouseButton : u8
	{
		LEFT = 0,
		MIDDLE,
		RIGHT,
		X1,
		X2,

		LAST //Last item
	};

	class DUCK_API InputManager
	{
	public:
		static void init(); //Called by Engine

		static bool is_key_down(Key key);
		static bool is_mouse_down(MouseButton mouse_button);

	private:
		static void sdl_key_down(SDL_Event& event);
		static void sdl_key_up(SDL_Event& event);

		static void sdl_mouse_down(SDL_Event& event);
		static void sdl_mouse_up(SDL_Event& event);

	private:
		static MouseButton sdl_to_mouse_button(u8 button);

		static std::map<SDL_Keycode, Key> m_sdl_keycode_to_key;
		static std::vector<bool> m_key_down;
		static std::vector<bool> m_mouse_down;

		static phmap::flat_hash_map<UID, std::function<void(void)>>* m_on_key_down_functions;
	};
}