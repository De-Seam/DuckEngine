#include "Events/InputManager.h"
#include "Events/SDLEventManager.h"

namespace DE //DuckEngine
{
	phmap::flat_hash_map<SDL_Keycode, Key> InputManager::m_sdlKeycodeToKey = {};
	Array<bool> InputManager::m_keyDown = {};
	Array<bool> InputManager::m_mouseDown = {};
	//phmap::flat_hash_map<UID, std::function<void(void)>>* InputManager::m_onKeyDownFunctions = nullptr;

	void InputManager::Init()
	{
		Log(LogType::Info, "Initializing InputManager");

		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_a] = Key::A;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_b] = Key::B;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_c] = Key::C;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_d] = Key::D;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_e] = Key::E;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_f] = Key::F;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_g] = Key::G;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_h] = Key::H;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_i] = Key::I;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_j] = Key::J;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_k] = Key::K;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_l] = Key::L;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_m] = Key::M;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_n] = Key::N;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_o] = Key::O;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_p] = Key::P;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_q] = Key::Q;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_r] = Key::R;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_s] = Key::S;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_t] = Key::T;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_u] = Key::U;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_v] = Key::V;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_w] = Key::W;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_x] = Key::X;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_y] = Key::Y;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_z] = Key::Z;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_1] = Key::ONE;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_2] = Key::TWO;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_3] = Key::THREE;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_4] = Key::FOUR;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_5] = Key::FIVE;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_6] = Key::SIX;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_7] = Key::SEVEN;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_8] = Key::EIGHT;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_9] = Key::NINE;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_0] = Key::ZERO;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_SLASH] = Key::FORWARDSLASH;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_BACKSLASH] = Key::BACKSLASH;
		m_sdlKeycodeToKey['<'] = Key::SMALLER;
		m_sdlKeycodeToKey['>'] = Key::BIGGER;
		m_sdlKeycodeToKey['.'] = Key::DOT;
		m_sdlKeycodeToKey[','] = Key::COMMA;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_LSHIFT] = Key::SHIFT;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_LCTRL] = Key::CONTROL;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_CAPSLOCK] = Key::CAPSLOCK;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_TAB] = Key::TAB;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_LALT] = Key::LEFTALT;
		m_sdlKeycodeToKey[SDL_KeyCode::SDLK_RALT] = Key::RIGHTALT;

		//m_onKeyDownFunctions = new phmap::flat_hash_map<UID, std::function<void(void)>>[static_cast<u_size>(Key::LAST)];
		m_keyDown.Resize(static_cast<u_size>(Key::LAST), false);
		m_mouseDown.Resize(static_cast<u_size>(MouseButton::LAST), false);

		SDLEventManager::AddEventFunction(SDLEventFunction{ SDL_KEYDOWN, &SDLKeyDown });
		SDLEventManager::AddEventFunction(SDLEventFunction{ SDL_KEYUP, &SDLKeyUp });

		SDLEventManager::AddEventFunction(SDLEventFunction{ SDL_MOUSEBUTTONDOWN, &SDLMouseDown });
		SDLEventManager::AddEventFunction(SDLEventFunction{ SDL_MOUSEBUTTONUP, &SDLMouseUp });
	}

	void InputManager::Cleanup()
	{
		Log(LogType::Info, "Cleanup InputManager");
	}

	bool InputManager::IsKeyDown(Key key)
	{
		assert(key != Key::LAST);
		return m_keyDown[static_cast<u_size>(key)];
	}

	bool InputManager::IsMouseDown(MouseButton mouse_button)
	{
		assert(mouse_button != MouseButton::LAST);
		return m_mouseDown[static_cast<u_size>(mouse_button)];;
	}

	void InputManager::SDLKeyDown(SDL_Event& event)
	{
		Key key = m_sdlKeycodeToKey[event.key.keysym.sym];
		m_keyDown[static_cast<u_size>(key)] = true;
	}
	void InputManager::SDLKeyUp(SDL_Event& event)
	{
		Key key = m_sdlKeycodeToKey[event.key.keysym.sym];
		m_keyDown[static_cast<u_size>(key)] = false;
	}

	void InputManager::SDLMouseDown(SDL_Event& event)
	{
		MouseButton button = SDLToMouseButton(event.button.button);
		m_mouseDown[static_cast<u_size>(button)] = true;
	}
	void InputManager::SDLMouseUp(SDL_Event& event)
	{
		MouseButton button = SDLToMouseButton(event.button.button);
		m_mouseDown[static_cast<u_size>(button)] = false;
	}

	MouseButton InputManager::SDLToMouseButton(u8 button)
	{
		switch (button)
		{
		case SDL_BUTTON_LEFT:
			return MouseButton::LEFT;
		case SDL_BUTTON_MIDDLE:
			return MouseButton::MIDDLE;
		case SDL_BUTTON_RIGHT:
			return MouseButton::RIGHT;
		case SDL_BUTTON_X1:
			return MouseButton::X1;
		case SDL_BUTTON_X2:
			return MouseButton::X2;
		}

		return MouseButton::LAST;
	}
}