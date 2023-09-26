#include "Resources/ResourceTypes/TextureResource.h"
#include "Renderer/Renderer.h"

#include <SDL/SDL_image.h>

namespace DE
{
	TextureResource::~TextureResource()
	{
		if (m_texture)
		{
			SDL_DestroyTexture(m_texture);
		}
	}

	void TextureResource::Load(const std::string& filePath)
	{
		SDL_Surface* imageSurface = IMG_Load(filePath.c_str());
		if (!imageSurface)
		{
			Log(LogType::Error, "Unable to load resource %s", filePath.c_str());
		}

		m_texture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), imageSurface);
		SDL_FreeSurface(imageSurface);
	}
}