#pragma once
#include "Core.h"

#include <SDL/SDL.h>
#include <phmap/phmap.h>

#include <functional>
#include <map>

namespace DE //DuckEngine
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

	class InputManager
	{
	public:
		static void Init(); //Called by Engine
		static void Cleanup(); //Called by Engine

		static bool IsKeyDown(Key key);
		static bool IsMouseDown(MouseButton mouse_button);

	private:
		static void SDLKeyDown(SDL_Event& event);
		static void SDLKeyUp(SDL_Event& event);

		static void SDLMouseDown(SDL_Event& event);
		static void SDLMouseUp(SDL_Event& event);

	private:
		static MouseButton SDLToMouseButton(u8 button);

		static std::map<SDL_Keycode, Key>* m_sdlKeycodeToKey;
		static Array<bool> m_keyDown;
		static Array<bool> m_mouseDown;

		//static phmap::flat_hash_map<UID, std::function<void(void)>>* m_onKeyDownFunctions;
	};
}