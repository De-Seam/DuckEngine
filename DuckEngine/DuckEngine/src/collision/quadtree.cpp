#include "de/collision/quadtree.h"
#include "de/entity/entity.h"
#include "de/engine/engine.h"

namespace de //DuckEngine
{
	void Quadtree::add_entity(UID uid)
	{
		Entity* entity = static_cast<Entity*>(de::Engine::get_object(uid));
		//if(!entity->has_component());
	}
}