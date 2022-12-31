#include "da/helper_functions.h"

namespace da
{
	fm::vec2 im_to_fm(ImVec2 vec)
	{
		return {vec.x, vec.y};
	}

	ImVec2 fm_to_im(fm::vec2 vec)
	{
		return {vec.x, vec.y};
	}
}