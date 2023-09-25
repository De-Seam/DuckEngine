#pragma once
#include "layer.h"

#include "DuckEngine/Core.h"
#include "DuckEngine/Engine/Engine.h"

#include "entt/entt.hpp"

class ViewportLayer : public Layer
{
public:
	ViewportLayer();
	virtual void Update(f32 dt) override;

	static LayerType GetType() { return LayerType::Viewport; }
	virtual LayerType GetTypeDynamic() override { return GetType(); }

	DE::Entity* GetSelectedEntity() { return m_selectedEntity; }
	void SetSelectedEntity(DE::Entity* entity);

private:
	fm::vec2 m_mouse_position = { 0.f,0.f };
	fm::vec2 m_position = { 0.f,0.f };
	fm::vec2 m_size = { 0.f, 0.f };
	DE::Entity* m_selectedEntity = nullptr;
};