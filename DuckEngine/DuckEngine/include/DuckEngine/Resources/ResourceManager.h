#pragma once
#include "Core.h"

#include <phmap/phmap.h>

namespace DE
{
	class Resource;

	class ResourceManager
	{
	public:
		static void Update(f64 dt);

		template<typename T>
		static std::shared_ptr<T> GetResource(const std::string& filePath);

		//Add resource to unload list. Will not unload if it's still being used
		static void UnloadResource(const std::string& filePath);
	private:
		static phmap::flat_hash_map<std::string, std::weak_ptr<Resource>> m_resources;

		friend class Resource;
	};

	template<typename T>
	inline std::shared_ptr<T> ResourceManager::GetResource(const std::string& filePath)
	{
		static_assert(std::is_base_of<Resource, T>::value, "T must derive from Resource");

		auto iter = m_resources.find(filePath);
		if (iter != m_resources.end()) {
			// Convert to SharedResource for use outside the manager.
			std::shared_ptr<Resource> sharedResource = iter->second.lock();
			if(sharedResource) //Make sure it's valid. If not, reload it.
				return std::static_pointer_cast<T>(sharedResource);
		}

		// Resource not found
		std::shared_ptr<T> resource = std::make_shared<T>();
		resource->m_filePath = filePath;
		resource->Load(filePath);
		m_resources[filePath] = resource;

		Log(LogType::Info, "Loaded Resource %s", filePath.c_str());

		std::shared_ptr<Resource> sharedResource = m_resources[filePath].lock();

		return std::static_pointer_cast<T>(sharedResource);
	}
}