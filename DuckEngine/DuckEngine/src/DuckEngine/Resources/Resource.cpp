#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"

namespace DE
{
	Resource::~Resource()
	{
		ResourceManager::UnloadResource(m_filePath);
	}

	void DE::Resource::Load(const std::string& filePath)
	{
		DE::Log(LogType::Error, "Tried to load empty resource with path %s", filePath.c_str());
	}
}
