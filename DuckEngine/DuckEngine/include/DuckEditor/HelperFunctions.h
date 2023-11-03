#pragma once
#ifdef DUCK_EDITOR

#include "Utils/FMath.h"

#include "imgui/imgui.h"

#include <filesystem>
#include <optional>

fm::vec2 IMToFM(ImVec2 vec);
ImVec2 FMToIM(fm::vec2 vec);

std::optional<std::string> SaveToFileExplorer(std::string startPath, const wchar_t* filter, const std::string& extension);
std::optional<std::string> OpenFromFileExplorer(const wchar_t* filter, const std::string& extension);

std::optional<std::string> TCHARToString(void* tchar);
std::wstring StringToWString(const std::string& str);
const wchar_t* CharToLPCWSTR(const char* charArray); //BEWARE: Cleanup yourself!

std::filesystem::path GetExecutablePath();

#endif
