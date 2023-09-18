#include "Editor/Layers/Layer.h"
#include "Editor/Editor.h"

Layer::Layer()
{
	if (Editor::AddLayer(this) != 0)
		delete this;
}

Layer::~Layer()
{
	Editor::DeleteLayer(this);
}