#pragma once
#include "DuckEngine/Core.h"

#include "DuckEngine/Resources/ResourceTypes/TextureResource.h""

namespace DE
{
struct TransformComponent
{
	fm::Transform transform;
};

struct RenderTextureComponent
{
	SharedPtr<TextureResource> texture;
};
}
