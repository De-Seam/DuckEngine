#pragma once
#include "de/core.h"

#include <phmap/phmap.h>

namespace de //DuckEngine
{
	enum class ResourceType
	{
		Invalid,
		Texture,
		Custom,
	};

	struct Resource : public Object
	{
		virtual void load_resource(const std::string& file_name) = 0;

		ResourceType resource_type = ResourceType::Invalid;
	private:
		friend class ResourceManager;
	};

	class DUCK_API ResourceManager
	{
	public:
		//Pre-load a resource for optimization purposes
		template<typename T>
		static T* load_resource(const std::string& file_name);
		template<typename T>
		static T* get_resource(const std::string& file_name);
		static void delete_resource(const std::string& file_name);
		static void delete_all_resources();

	private:
		static phmap::flat_hash_map<std::string, Resource*> m_resources;
	};

	template<typename T>
	inline T* ResourceManager::load_resource(const std::string& file_name)
	{
		//Make sure it isn't already loaded
		assert(m_resources.find(file_name) == m_resources.end());
		T* resource = new T;
		resource->load_resource(file_name);
		m_resources[file_name] = resource;
		return resource;
	}

	template<typename T>
	inline T* ResourceManager::get_resource(const std::string& file_name)
	{
		if(m_resources.find(file_name) == m_resources.end()) 
		{
			//Load resource
			return load_resource<T>(file_name);
		}
		return reinterpret_cast<T*>(m_resources[file_name]);
	}
}