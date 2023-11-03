#include "DuckEditor/Layers/MainMenuBarLayer.h"
#include "Engine/Engine.h"

#include <Windows.h>
#include <algorithm>
#include <locale>
#include <codecvt>

MainMenuBarLayer::MainMenuBarLayer()
{}

std::wstring ExePath()
{
	TCHAR buffer[MAX_PATH] = {0};
	GetModuleFileName(nullptr, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
}

std::optional<std::string> SaveFileExplorer()
{
	OPENFILENAME ofn;

	TCHAR NPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, NPath);

	// Append a trailing backslash to the current directory if it's not already there
	if (NPath[lstrlen(NPath) - 1] != '\\')
	{
		lstrcat(NPath, L"\\");

		std::string worldFilePath = DE::Engine::GetWorld()->GetFilePath();
		std::replace(worldFilePath.begin(), worldFilePath.end(), '/', '\\');

		// Initializing an object of wstring
		std::wstring temp = std::wstring(worldFilePath.begin(), worldFilePath.end());

		// Applying c_str() method on temp
		LPCWSTR wideString = temp.c_str();

		lstrcat(NPath, wideString);
	}

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFilter = static_cast<LPCWSTR>(L"DuckMap Files (*.DuckMap)\0*.DuckMap\0All Files (*.*)\0*.*\0");
	ofn.lpstrFile = static_cast<LPWSTR>(NPath);
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = static_cast<LPCWSTR>(L".DuckMap");

	if (GetSaveFileName(&ofn))
	{
#ifdef UNICODE
		std::vector<char> buffer;
		int size = WideCharToMultiByte(CP_UTF8, 0, NPath, -1, nullptr, 0, nullptr, nullptr);
		if (size > 0)
		{
			buffer.resize(size);
			WideCharToMultiByte(CP_UTF8, 0, NPath, -1, buffer.data(), static_cast<int>(buffer.size()), nullptr, nullptr);
		}
		else
		{
			Log(DE::LogType::Error, "Error opening file");
			return std::nullopt;
		}
		//*/
		std::string savedPath(buffer.data());
#else
		std::string savedPath = NPath;
#endif
		return savedPath;
	}
	return std::nullopt;
}

std::optional<std::string> OpenFileExplorer()
{
	OPENFILENAME ofn;
	TCHAR NPath[MAX_PATH];
	ZeroMemory(&NPath, sizeof(NPath));
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFilter = static_cast<LPCWSTR>(L"DuckMap Files (*.DuckMap)\0*.DuckMap\0All Files (*.*)\0*.*\0");
	ofn.lpstrFile = static_cast<LPWSTR>(NPath);
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = static_cast<LPCWSTR>(L".DuckMap");

	if (GetOpenFileName(&ofn))
	{
#ifdef UNICODE
		std::vector<char> buffer;
		int size = WideCharToMultiByte(CP_UTF8, 0, NPath, -1, nullptr, 0, nullptr, nullptr);
		if (size > 0)
		{
			buffer.resize(size);
			WideCharToMultiByte(CP_UTF8, 0, NPath, -1, buffer.data(), static_cast<int>(buffer.size()), nullptr, nullptr);
		}
		else
		{
			Log(DE::LogType::Error, "Error opening file");
			return std::nullopt;
		}
		//*/
		std::string openedPath(buffer.data());
#else
		std::string openedPath = NPath;
#endif
		return openedPath;
	}
	return std::nullopt;
}

void MainMenuBarLayer::Update(f64)
{
	if (ImGui::BeginMainMenuBar())
	{
		// Create a "File" menu with a dropdown
		if (ImGui::BeginMenu("File"))
		{
			// Add a "Save" button inside the dropdown
			if (ImGui::MenuItem("Save"))
			{
				std::optional<std::string> savedPath = SaveFileExplorer();
				if (savedPath.has_value())
				{
					DE::Engine::GetWorld()->SaveToFile(savedPath.value());
				}
			}

			// Add an "Open" button inside the dropdown
			if (ImGui::MenuItem("Open"))
			{
				std::optional<std::string> openedPath = OpenFileExplorer();
				if (openedPath.has_value())
				{
					DE::Engine::LoadWorldFromFile(openedPath.value().c_str());
				}
			}

			// End the "File" menu
			ImGui::EndMenu();
		}

		// End the main menu bar
		ImGui::EndMainMenuBar();
	}
}
