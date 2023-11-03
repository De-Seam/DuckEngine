#pragma once
#include "DuckEngine/Core.h"

#include "DuckEngine/Resources/ResourceTypes/TextureResource.h"

namespace DE
{
struct TransformComponent
{
	fm::Transform transform;
};

struct RenderTextureComponent
{
	std::shared_ptr<TextureResource> texture;
};
}
