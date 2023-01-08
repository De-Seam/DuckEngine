#include "de/ecs/components/render_components.h"

#include "de/engine/resource_manager.h"
#include "de/engine/resources.h"

namespace de
{
	RenderTextureComponent::RenderTextureComponent(TextureResource* resource)
		: texture_resource(texture_resource)
	{}

	RenderTextureComponent::RenderTextureComponent(const std::string& file_name)
	{
		texture_resource = ResourceManager::get_resource<TextureResource>(file_name);
	}
}