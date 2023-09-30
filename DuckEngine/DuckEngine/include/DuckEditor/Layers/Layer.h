#pragma once
#ifdef DUCK_EDITOR

#include "DuckEditor/HelperFunctions.h"

#include "Core.h"

#include "imgui/imgui.h"

enum class LayerType : uint32_t
{
	Invalid,
	Viewport,
	Outliner,
	Inspector,
};

//Layer base class
class Layer
{
public:
	Layer() = default;
	virtual ~Layer() = default;

	virtual void Update([[maybe_unused]] f64 dt) {}

	//Overwrite this!
	static LayerType GetType() { return LayerType::Invalid; }
	virtual LayerType GetTypeDynamic() { return GetType(); }

	virtual void DestroyLayer();

	ImGuiContext* GetContext() { return m_context; }

protected:
	ImGuiContext* m_context = nullptr;
};

#endif
