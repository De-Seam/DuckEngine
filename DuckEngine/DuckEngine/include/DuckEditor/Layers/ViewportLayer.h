#pragma once
#ifdef DUCK_EDITOR

#define FRAMETIME_COUNT 256

#include "layer.h"

#include "DuckEngine/Core.h"
#include "DuckEngine/Engine/Engine.h"

#include "entt/entt.hpp"

namespace DE
{
class TextureResource;
}

class ViewportLayer : public Layer
{
public:
	ViewportLayer();
	virtual ~ViewportLayer() override = default;
	virtual void Update(f32 dt) override;
	void FPSCounter(f32 dt);
	bool CameraController();
	void EntitySelector();

	static LayerType GetType() { return LayerType::Viewport; }
	virtual LayerType GetTypeDynamic() override { return GetType(); }

	std::weak_ptr<DE::Entity> GetSelectedEntity() const { return m_selectedEntity; }
	void SetSelectedEntity(std::shared_ptr<DE::Entity> entity);

private:
	fm::vec2 m_lastFrameMousePosition = {0.f, 0.f};
	fm::vec2 m_position = {0.f, 0.f};
	fm::vec2 m_size = {0, 0};
	std::weak_ptr<DE::Entity> m_selectedEntity;

	f32 m_frameTimes[FRAMETIME_COUNT] = {};
	u_size m_currentFrameTimeIndex = 0;

	fm::vec2 m_lastFrameMousePos = {0, 0};

	std::shared_ptr<DE::TextureResource> m_selectedOutlineTexture = nullptr;
};

#endif
