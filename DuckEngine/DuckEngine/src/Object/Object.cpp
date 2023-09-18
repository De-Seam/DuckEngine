#include "Object/Object.h"

#include "Engine/Engine.h"

#include <typeinfo>

namespace DE
{
	Object::Object(const char* name)
	{
		className = name;
		Engine::AddObject(this);
	}

	Object::~Object()
	{
		Engine::RemoveObject(this);
	}
}