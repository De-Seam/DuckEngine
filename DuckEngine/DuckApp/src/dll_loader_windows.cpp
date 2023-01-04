#include "da/dll_loader.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace da
{
	phmap::flat_hash_map<std::string, DllInstance> DllLoader::m_dlls = {};

	void DllLoader::load_dll(const std::string& file)
	{
		HINSTANCE dll_instance = LoadLibraryA(file.c_str());
		if (dll_instance == NULL)
		{
			de::log(de::LogType::error, "Invalid DLL!");
		}
		m_dlls[file] = DllInstance(new HINSTANCE(dll_instance));
	}

	void DllLoader::unload_dll(const std::string& file)
	{
		FreeLibrary(*m_dlls[file].get<HINSTANCE>());
	}

	void DllLoader::reload_dll(const std::string& file)
	{
		unload_dll(file);
		load_dll(file);
	}

}