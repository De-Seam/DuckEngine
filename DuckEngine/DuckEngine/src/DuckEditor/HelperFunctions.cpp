#ifdef DUCK_EDITOR

#include "DuckEditor/HelperFunctions.h"

fm::vec2 IMToFM(ImVec2 vec)
{
	return {vec.x, vec.y};
}

ImVec2 FMToIM(fm::vec2 vec)
{
	return {vec.x, vec.y};
}

#endif
