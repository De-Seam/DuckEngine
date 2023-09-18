#pragma once
#include "Layers/Layer.h"
#include "HelperFunctions.h"

#include "Core.h"

#include "phmap/phmap.h"
#include "SDL/SDL.h"

enum class GameState
{
	NotPlaying,
	Playing,
	Paused
};

class Editor
{
public:
	static void Init();

	static SDL_Texture*& GetViewportTexture();
private:
	static void Update(f64 dt);

	//0 on success
	static int AddLayer(Layer*);
	static int DeleteLayer(Layer*);
private:
	static GameState m_gameState;

	static phmap::flat_hash_map<LayerType, Layer*> m_layers;

	static SDL_Texture* m_viewportTexture;

	friend class Layer;
	friend class App;
};