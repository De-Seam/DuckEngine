#include "da/editor/layers/layer.h"
#include "da/editor/editor.h"

namespace da
{
	Layer::Layer()
	{
		if(Editor::add_layer(this) != 0)
			delete this;
	}

	Layer::~Layer()
	{
		Editor::delete_layer(this);
	}
}