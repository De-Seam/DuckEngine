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

void MainMenuBarLayer::Update(f32)
{
	if (ImGui::BeginMainMenuBar())
	{
		// Create a "File" menu with a dropdown
		if (ImGui::BeginMenu("File"))
		{
			// Add a "Save" button inside the dropdown
			if (ImGui::MenuItem("Save"))
			{
				std::optional<std::string> savedPath = SaveToFileExplorer(DE::Engine::GetWorld()->GetFilePath(),
																		L"DuckWorld Files (*.DuckWorld)\0*.DuckWorld\0All Files (*.*)\0*.*\0", "DuckWorld");
				if (savedPath.has_value())
				{
					DE::Engine::GetWorld()->SaveToFile(savedPath.value());
				}
			}

			// Add an "Open" button inside the dropdown
			if (ImGui::MenuItem("Open"))
			{
				std::optional<std::string> openedPath =
					OpenFromFileExplorer(L"DuckWorld Files (*.DuckWorld)\0*.DuckWorld\0All Files (*.*)\0*.*\0", "DuckWorld");
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
