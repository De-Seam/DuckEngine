#pragma once
#include "Layers/Layer.h"
#include "HelperFunctions.h"

#include "Core.h"

#include "phmap/phmap.h"
#include "SDL/SDL.h"

#define IMGUI_VAR(func, label, code) ImGui::TextUnformatted(label); ImGui::NextColumn(); ImGui::SetNextItemWidth(-1); if(func) { code } ImGui::NextColumn();

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

	template<typename T>
	static T* GetLayer();

	template<typename T>
	static void CreateLayer();
	template<typename T>
	static void DestroyLayer();

	static void DestroyLayer(LayerType layerType);

private:
	static void Update(f64 dt);

private:
	static GameState m_gameState;

	static phmap::flat_hash_map<LayerType, std::unique_ptr<Layer>> m_layers;

	static SDL_Texture* m_viewportTexture;

	friend class Layer;
	friend class App;
};

template<typename T>
inline T* Editor::GetLayer()
{
	static_assert(std::is_base_of<Layer, T>::value, "T must derive from Layer");

	return static_cast<T*>(m_layers[T::GetType()].get());
}

template<typename T>
inline void Editor::CreateLayer()
{
	static_assert(std::is_base_of<Layer, T>::value, "T must derive from Layer");

	DE::Log(DE::LogType::Info, "Creating Layer %s", typeid(T).name());
	std::unique_ptr<T> layer = std::make_unique<T>();
	m_layers[layer->GetType()] = std::move(layer);
}

template<typename T>
inline void Editor::DestroyLayer()
{
	static_assert(std::is_base_of<Layer, T>::value, "T must derive from Layer");

	DE::Log(DE::LogType::Info, "Destroying Layer %s", typeid(T).name());
	DestroyLayer(T::GetType());
}
