#pragma once
#include "de/core.h"
#include "de/utils/uid.h"

namespace de
{
	class DUCK_API Object
	{
	public:
		Object();

		UID uid = {};
	};
}