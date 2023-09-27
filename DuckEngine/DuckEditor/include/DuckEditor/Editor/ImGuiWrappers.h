#pragma once
#include "DuckEngine/Core.h"
#include "DuckEngine/Resources/ResourceTypes/TextureResource.h"

#include <imgui/imgui.h>

#include <vector>
#include <algorithm>

struct ColumnDragScalar
{
	struct PerScalarData
	{
		const char* label;
		std::shared_ptr<DE::TextureResource> texture;
	};

	void Update(void* data[])
	{
		ImGui::TextUnformatted(text.c_str());
		ImGui::NextColumn();

		const float availableWidth = ImGui::GetContentRegionAvail().x;
		const float dragWidth = std::max(minWidth, availableWidth * (1.f / static_cast<float>(perScalarData.size()))); // Adjust the multiplier as needed

		for (u_size i = 0; i < perScalarData.size(); i++)
		{
			if(i != 0)
				ImGui::SameLine(0.f, 0.f);
			PerScalarData& currentScalarData = perScalarData[i];
			if (currentScalarData.texture)
			{
				ImGui::Image(ImTextureID(currentScalarData.texture->GetTexture()), ImVec2(19, 19), ImVec2(0, 0), ImVec2(1, 1));
				ImGui::SameLine(0.f, 0.f);
			}
			ImGui::SetNextItemWidth(dragWidth);
			ImGui::DragScalar(currentScalarData.label, dataType, data[i], speed, min, max, format);
		}

		ImGui::NextColumn();
	}

	std::string text;
	std::vector<PerScalarData> perScalarData;
	ImGuiDataType dataType = ImGuiDataType_Double;

	float speed = 1.f;
	void* min = 0;
	void* max = 0;
	const char* format = "%.3f";

	float minWidth = 40.f;
};