#ifdef DUCK_EDITOR

#include "DuckEditor/Layers/Layer.h"
#include "DuckEditor/Editor.h"

void Layer::DestroyLayer()
{
	Editor::DestroyLayer(GetTypeDynamic());
}

#endif
