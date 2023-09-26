#pragma once
#include "layer.h"

#include "DuckEngine/Core.h"

#include "entt/entt.hpp"

class InspectorLayer : public Layer
{
public:
	InspectorLayer();
	virtual void Update(f32 dt) override;

	static LayerType GetType() { return LayerType::Inspector; }
	virtual LayerType GetTypeDynamic() override { return GetType(); }

private:
};