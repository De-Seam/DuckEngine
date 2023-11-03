#ifdef DUCK_EDITOR
#include "DuckEditor/HelperFunctions.h"

#include "Engine/Engine.h"

#include <Windows.h>

fm::vec2 IMToFM(ImVec2 vec)
{
	return {vec.x, vec.y};
}

ImVec2 FMToIM(fm::vec2 vec)
{
	return {vec.x, vec.y};
}

std::optional<std::string> SaveToFileExplorer(std::string startPath, const wchar_t* filter, const std::string& extension)
{
	TCHAR currentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentDir);

	OPENFILENAME ofn;

	TCHAR NPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, NPath);

	// Append a trailing backslash to the current directory if it's not already there
	if (NPath[lstrlen(NPath) - 1] != '\\')
	{
		lstrcat(NPath, L"\\");

		std::replace(startPath.begin(), startPath.end(), '/', '\\');

		// Initializing an object of wstring
		std::wstring temp = std::wstring(startPath.begin(), startPath.end());

		// Applying c_str() method on temp
		LPCWSTR wideString = temp.c_str();

		lstrcat(NPath, wideString);
	}

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = static_cast<LPWSTR>(NPath);
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	std::wstring extensionW = StringToWString(extension);
	LPCWSTR extensionL = extensionW.c_str();
	ofn.lpstrDefExt = extensionL;

	if (GetSaveFileName(&ofn))
	{
		std::optional<std::string> savedPath = TCHARToString(NPath);
		if (!savedPath)
		{
			Log(DE::LogType::Error, "Error opening file");
			SetCurrentDirectory(currentDir);
			return std::nullopt;
		}
		SetCurrentDirectory(currentDir);
		return savedPath.value();
	}
	SetCurrentDirectory(currentDir);
	return std::nullopt;
}

std::optional<std::string> OpenFromFileExplorer(const wchar_t* filter, const std::string& extension)
{
	TCHAR currentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentDir);

	OPENFILENAME ofn;
	TCHAR NPath[MAX_PATH];
	ZeroMemory(&NPath, sizeof(NPath));
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = static_cast<LPWSTR>(NPath);
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = StringToWString(extension).c_str();

	if (GetOpenFileName(&ofn))
	{
		std::optional<std::string> openedPath = TCHARToString(NPath);
		if (!openedPath)
		{
			Log(DE::LogType::Error, "Error opening file");
			SetCurrentDirectory(currentDir);
			return std::nullopt;
		}
		SetCurrentDirectory(currentDir);
		return openedPath.value();
	}
	SetCurrentDirectory(currentDir);
	return std::nullopt;
}

std::optional<std::string> TCHARToString(void* tchar)
{
#ifdef UNICODE
	std::vector<char> buffer;
	int size = WideCharToMultiByte(CP_UTF8, 0, static_cast<TCHAR*>(tchar), -1, nullptr, 0, nullptr, nullptr);
	if (size > 0)
	{
		buffer.resize(size);
		WideCharToMultiByte(CP_UTF8, 0, static_cast<TCHAR*>(tchar), -1, buffer.data(), static_cast<int>(buffer.size()), nullptr, nullptr);
	}
	else
	{
		return std::nullopt;
	}
	//*/
	std::string str(buffer.data());
#else
	std::string str = NPath;
#endif

	return str;
}

std::wstring StringToWString(const std::string& str)
{
	if (str.empty()) return std::wstring();

	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), nullptr, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), &wstrTo[0], size_needed);
	return wstrTo;
}

LPCWSTR CharToLPCWSTR(const char* charArray)
{
	int wideCharArraySize = MultiByteToWideChar(CP_UTF8, 0, charArray, -1, nullptr, 0);

	// Allocate memory for the wide char array
	wchar_t* wideCharArray = new wchar_t[wideCharArraySize];

	// Perform the conversion
	MultiByteToWideChar(CP_UTF8, 0, charArray, -1, wideCharArray, wideCharArraySize);

	// Return the wide char array
	return wideCharArray;
}

std::filesystem::path GetExecutablePath()
{
	wchar_t path[MAX_PATH] = {0};
	GetModuleFileNameW(nullptr, path, MAX_PATH);
	return std::filesystem::path(path).parent_path();
}

#endif
