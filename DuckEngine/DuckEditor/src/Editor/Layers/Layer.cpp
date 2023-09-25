#include "Editor/Layers/Layer.h"
#include "Editor/Editor.h"

void Layer::DestroyLayer()
{
	Editor::DestroyLayer(GetTypeDynamic());
}
