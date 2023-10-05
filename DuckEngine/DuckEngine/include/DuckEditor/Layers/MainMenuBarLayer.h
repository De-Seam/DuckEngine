#pragma once
#ifdef DUCK_EDITOR

#include "layer.h"
#include "DuckEditor//ImGuiWrappers.h"

#include "DuckEngine/Core.h"

class MainMenuBarLayer : public Layer
{
public:
	MainMenuBarLayer();
	virtual void Update(f64 dt) override;

	static LayerType GetType() { return LayerType::MainMenuBar; }
	virtual LayerType GetTypeDynamic() override { return GetType(); }

private:
	ColumnDragScalar m_positionColum;
	ColumnDragScalar m_sizeColum;
	ColumnDragScalar m_rotationColum;
};

#endif
