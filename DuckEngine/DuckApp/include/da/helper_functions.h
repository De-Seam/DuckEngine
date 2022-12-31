#pragma once

#include "de/utils/fmath.h"

#include "imgui/imgui.h"

namespace da
{
	fm::vec2 im_to_fm(ImVec2 vec);
	ImVec2 fm_to_im(fm::vec2 vec);
}