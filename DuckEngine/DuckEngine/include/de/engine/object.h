#pragma once
#include "de/core.h"
#include "de/utils/uid.h"

namespace de
{
	//An object can be anything the game uses. 
	//It's the base class for Entity, and other things such as structs we need to keep track of
	class DUCK_API Object
	{
	public:
		Object();
		~Object();

		UID uid = {};
	};
}