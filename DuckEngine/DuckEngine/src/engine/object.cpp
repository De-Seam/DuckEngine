#include "de/engine/object.h"
#include "de/engine/engine.h"

namespace de
{
	Object::Object()
	{
		Engine::add_object(this);
	}
}