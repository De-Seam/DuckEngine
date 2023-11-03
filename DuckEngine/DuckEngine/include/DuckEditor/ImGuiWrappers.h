#pragma once
#ifdef DUCK_EDITOR

#include "DuckEngine/Core.h"
#include "DuckEngine/Resources/ResourceTypes/TextureResource.h"

#include <imgui/imgui.h>

#include <vector>
#include <algorithm>
#include <functional>

struct ColumnDragScalar
{
	struct PerScalarData
	{
		const char* label;
		std::shared_ptr<DE::TextureResource> texture;
		std::function<void(void* currentData)> ifEditedFunction = nullptr;
	};

	void Update(void* data[])
	{
		ImGui::TextUnformatted(text.c_str());
		ImGui::NextColumn();

		const float availableWidth = ImGui::GetContentRegionAvail().x;
		const float dragWidth = std::max(minWidth, availableWidth * (1.f / static_cast<float>(perScalarData.size())));
		// Adjust the multiplier as needed

		for (u_size i = 0; i < perScalarData.size(); i++)
		{
			if (i != 0)
				ImGui::SameLine(0.f, 0.f);
			PerScalarData& currentScalarData = perScalarData[i];
			if (currentScalarData.texture)
			{
				ImGui::Image(currentScalarData.texture->GetTexture(), ImVec2(19, 19),
							ImVec2(0, 0), ImVec2(1, 1));
				ImGui::SameLine(0.f, 0.f);
			}
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragScalar(currentScalarData.label, dataType, data[i], speed, min, max, format))
			{
				if (currentScalarData.ifEditedFunction)
					currentScalarData.ifEditedFunction(data[i]);
			}
		}

		ImGui::NextColumn();
	}

	std::string text;
	std::vector<PerScalarData> perScalarData;
	ImGuiDataType dataType = ImGuiDataType_Float;

	float speed = 1.f;
	void* min = nullptr;
	void* max = nullptr;
	const char* format = "%.3f";

	float minWidth = 40.f;
};

#endif
