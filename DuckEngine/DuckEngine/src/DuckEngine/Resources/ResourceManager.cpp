#include "Resources/ResourceManager.h"

#include "Resources/Resource.h"

namespace DE
{
	phmap::flat_hash_map<std::string, std::weak_ptr<Resource>> ResourceManager::m_resources = {};
	
	void ResourceManager::UnloadResource(const std::string& filePath)
	{
		Log(LogType::Info, "Unloaded resource %s ", filePath.c_str());
		m_resources.erase(filePath);
	}
}