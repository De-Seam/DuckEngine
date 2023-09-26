#pragma once
#include "layer.h"

#include "DuckEngine/Core.h"

#include "entt/entt.hpp"

class OutlinerLayer : public Layer
{
public:
	OutlinerLayer();
	virtual void Update(f32 dt) override;

	static LayerType GetType() { return LayerType::Outliner; }
	virtual LayerType GetTypeDynamic() override { return GetType(); }

private:
};