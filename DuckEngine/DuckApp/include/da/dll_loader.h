#pragma once
#include "de/core.h"

#include "phmap/phmap.h"

namespace da //DuckApp
{
	struct DllInstance
	{
		DllInstance() : data(nullptr) {}
		DllInstance(void* data) : data(data) {}

		template<typename T>
		T* get() { return reinterpret_cast<T*>(data); }
		void* data;
	};

	class DllLoader
	{
	public:
		static void load_dll(const std::string& file);
		static void unload_dll(const std::string& file);
		static void reload_dll(const std::string& file);

	private:
		static phmap::flat_hash_map<std::string, DllInstance> m_dlls;
	};
}