#pragma once
#include "HelperFunctions.h"

#include "Core.h"

#include "imgui/imgui.h"
enum class LayerType : uint32_t
{
	Invalid,
	Viewport,
};

//Layer base class
class Layer
{
public:
	Layer();
	~Layer();

	virtual void update([[maybe_unused]] f32 dt) {}

	LayerType get_type() { return m_type; }
	ImGuiContext* get_context() { return m_context; }
protected:
	LayerType m_type = LayerType::Viewport;
	ImGuiContext* m_context = nullptr;
};