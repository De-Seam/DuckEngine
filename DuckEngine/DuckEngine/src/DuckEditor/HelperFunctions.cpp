#ifdef DUCK_EDITOR

#include "DuckEditor/HelperFunctions.h"

fm::vec2 IMToFM(ImVec2 vec)
{
	return {static_cast<double>(vec.x), static_cast<double>(vec.y)};
}

ImVec2 FMToIM(fm::vec2 vec)
{
	return {static_cast<float>(vec.x), static_cast<float>(vec.y)};
}

#endif
