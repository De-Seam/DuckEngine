#include "de/events/input_manager.h"
#include "de/events/sdl_event_manager.h"

namespace de //DuckEngine
{
	std::map<SDL_Keycode, Key> InputManager::m_sdl_keycode_to_key =  {};
	std::vector<bool> InputManager::m_key_down = {};
	std::vector<bool> InputManager::m_mouse_down = {};
	phmap::flat_hash_map<UID, std::function<void(void)>>* InputManager::m_on_key_down_functions = nullptr;

	void InputManager::init()
	{
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_a] = Key::A;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_b] = Key::B;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_c] = Key::C;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_d] = Key::D;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_e] = Key::E;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_f] = Key::F;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_g] = Key::G;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_h] = Key::H;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_i] = Key::I;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_j] = Key::J;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_k] = Key::K;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_l] = Key::L;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_m] = Key::M;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_n] = Key::N;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_o] = Key::O;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_p] = Key::P;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_q] = Key::Q;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_r] = Key::R;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_s] = Key::S;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_t] = Key::T;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_u] = Key::U;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_v] = Key::V;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_w] = Key::W;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_x] = Key::X;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_y] = Key::Y;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_z] = Key::Z;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_1] = Key::ONE;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_2] = Key::TWO;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_3] = Key::THREE;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_4] = Key::FOUR;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_5] = Key::FIVE;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_6] = Key::SIX;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_7] = Key::SEVEN;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_8] = Key::EIGHT;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_9] = Key::NINE;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_0] = Key::ZERO;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_SLASH] = Key::FORWARDSLASH;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_BACKSLASH] = Key::BACKSLASH;
		m_sdl_keycode_to_key['<'] = Key::SMALLER;
		m_sdl_keycode_to_key['>'] = Key::BIGGER;
		m_sdl_keycode_to_key['.'] = Key::DOT;
		m_sdl_keycode_to_key[','] = Key::COMMA;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_LSHIFT] = Key::SHIFT;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_LCTRL] = Key::CONTROL;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_CAPSLOCK] = Key::CAPSLOCK;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_TAB] = Key::TAB;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_LALT] = Key::LEFTALT;
		m_sdl_keycode_to_key[SDL_KeyCode::SDLK_RALT] = Key::RIGHTALT;

		m_on_key_down_functions = new phmap::flat_hash_map<UID, std::function<void(void)>>[static_cast<u_size>(Key::LAST)];
		m_key_down.resize(static_cast<u_size>(Key::LAST), false);
		m_mouse_down.resize(static_cast<u_size>(MouseButton::LAST), false);

		SDLEventManager::add_event_function(SDLEventFunction{SDL_KEYDOWN, &sdl_key_down});
		SDLEventManager::add_event_function(SDLEventFunction{SDL_KEYUP, &sdl_key_up});

		SDLEventManager::add_event_function(SDLEventFunction{SDL_MOUSEBUTTONDOWN, &sdl_mouse_down});
		SDLEventManager::add_event_function(SDLEventFunction{SDL_MOUSEBUTTONUP, &sdl_mouse_up});
	}

	bool InputManager::is_key_down(Key key)
	{
		assert(key != Key::LAST);
		return m_key_down[static_cast<u_size>(key)];
	}

	bool InputManager::is_mouse_down(MouseButton mouse_button)
	{
		assert(mouse_button != MouseButton::LAST);
		return m_mouse_down[static_cast<u_size>(mouse_button)];;
	}

	void InputManager::sdl_key_down(SDL_Event& event)
	{
		Key key = m_sdl_keycode_to_key[event.key.keysym.sym];
		m_key_down[static_cast<u_size>(key)] = true;
	}
	void InputManager::sdl_key_up(SDL_Event& event)
	{
		Key key = m_sdl_keycode_to_key[event.key.keysym.sym];
		m_key_down[static_cast<u_size>(key)] = false;
	}

	void InputManager::sdl_mouse_down(SDL_Event& event)
	{
		MouseButton button = sdl_to_mouse_button(event.button.button);
		m_mouse_down[static_cast<u_size>(button)] = true;
	}
	void InputManager::sdl_mouse_up(SDL_Event& event)
	{
		MouseButton button = sdl_to_mouse_button(event.button.button);
		m_mouse_down[static_cast<u_size>(button)] = false;
	}

	MouseButton InputManager::sdl_to_mouse_button(u8 button)
	{
		switch(button)
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
	}
}