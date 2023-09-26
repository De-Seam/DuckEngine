#pragma once
#include "Core.h"

namespace DE
{
	class Resource
	{
	public:
		~Resource();

		virtual void Load(const std::string& filePath);

		const std::string& GetFilePath()
		{
			return m_filePath;
		}
	private:
		std::string m_filePath; //Set by ResourceManager, before Load() is called

		friend class ResourceManager;
	};
}