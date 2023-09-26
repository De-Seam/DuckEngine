#pragma once
#include "Core.h"
#include "Resources/Resource.h"

#include <SDL/SDL.h>

namespace DE
{
	class TextureResource : public Resource
	{
	public:
		~TextureResource();
		virtual void Load(const std::string& filePath) override;

		SDL_Texture* GetTexture()
		{
			return m_texture;
		}
	private:
		SDL_Texture* m_texture = nullptr;
	};
}