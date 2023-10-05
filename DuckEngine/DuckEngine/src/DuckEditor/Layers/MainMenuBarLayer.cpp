#include "DuckEditor/Layers/MainMenuBarLayer.h"
#include "Engine/Engine.h"

#include <Windows.h>
#include <algorithm>

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
	DWORD a = GetCurrentDirectory(MAX_PATH, NPath);

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
		std::wstring wStr = NPath;
		std::string savedPath = std::string(wStr.begin(), wStr.end());
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
		std::wstring wStr = NPath;
		std::string openedPath = std::string(wStr.begin(), wStr.end());
		return openedPath;
	}
	return std::nullopt;
}

void MainMenuBarLayer::Update(f64 dt)
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
