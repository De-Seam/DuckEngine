#pragma once
#include "layers/layer.h"
#include "da/helper_functions.h"

#include "de/core.h"

#include "phmap/phmap.h"
#include "SDL/SDL.h"

namespace da
{
	class Editor
	{
	public:
		static void init();

		static SDL_Texture*& get_viewport_texture();
	private:
		static void main_loop();
		static void update(f32 dt);

		//0 on success
		static int add_layer(Layer*);
		static int delete_layer(Layer*);


	private:
		static bool m_is_running;
		static f32 m_delta_time;

		static phmap::flat_hash_map<LayerType, Layer*> m_layers;

		static SDL_Texture* m_viewport_texture;

		friend class Layer;
	};
}