#pragma once
#include "layer.h"
#include "Editor/ImGuiWrappers.h"

#include "DuckEngine/Core.h"

#include "entt/entt.hpp"

class InspectorLayer : public Layer
{
public:
	InspectorLayer();
	virtual void Update(f64 dt) override;

	static LayerType GetType() { return LayerType::Inspector; }
	virtual LayerType GetTypeDynamic() override { return GetType(); }

private:
	ColumnDragScalar m_positionColum;
	ColumnDragScalar m_sizeColum;
	ColumnDragScalar m_rotationColum;
};