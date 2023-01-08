#include "de/engine/resource_manager.h"

namespace de //DuckEngine
{
	phmap::flat_hash_map<std::string, Resource*> ResourceManager::m_resources = {};

	void ResourceManager::delete_resource(const std::string& file_name)
	{
		delete m_resources[file_name];
		m_resources.erase(file_name);
	}

	void ResourceManager::delete_all_resources()
	{
		for(auto& resource: m_resources)
			delete resource.second;
		m_resources.clear();
	}
}