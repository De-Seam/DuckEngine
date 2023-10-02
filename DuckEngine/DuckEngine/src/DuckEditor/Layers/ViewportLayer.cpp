#ifdef DUCK_EDITOR

#include "DuckEditor/Layers/ViewportLayer.h"
#include "DuckEditor/Editor.h"
#include "DuckEditor/Layers/InspectorLayer.h"

#include "DuckEngine/Resources/ResourceManager.h"
#include "DuckEngine/Resources/ResourceTypes/TextureResource.h"
#include "DuckEngine/Engine/Engine.h"
#include "DuckEngine/Renderer/Renderer.h"

ViewportLayer::ViewportLayer()
{
	std::fill_n(m_frameTimes, FRAMETIME_COUNT, 0.1);

	m_selectedOutlineTexture = DE::ResourceManager::GetResource<DE::TextureResource>(
		"Assets/Editor/Textures/SelectedOutline.png");
}

void ViewportLayer::Update(f64 dt)
{
	ImGui::Begin("Viewport##LayerWindow");
	{
		m_context = ImGui::GetCurrentContext();

		if (ImGui::Button("Play##ViewportPlayButton"))
			DE::Engine::BeginPlay();

		ImGui::SameLine();

		FPSCounter(dt);

		ImGui::BeginChild("ViewportGame", {0, 0}, false, ImGuiWindowFlags_NoMove);
		{
			m_position = IMToFM(ImGui::GetWindowPos());

			ImVec2 imWindowSize = ImGui::GetWindowSize();
			ImGui::Image(Editor::GetViewportTexture(), imWindowSize);

			fm::vec2 windowSize = IMToFM(imWindowSize);
			if (windowSize.x != m_size.x ||
				windowSize.y != m_size.y)
			{
				Editor::ResizeViewport(fm::ivec2(static_cast<i32>(windowSize.x), static_cast<i32>(windowSize.y)));
				m_size = windowSize;
			}

			//If we're not controlling the camera, go to the entity selector
			if (!CameraController())
				EntitySelector();

			if (m_selectedEntity)
			{
				fm::vec2 outlineScale = m_selectedEntity->GetSize() / fm::vec2(512, 512);
				DE::Renderer::DrawTextureTinted(m_selectedOutlineTexture->GetTexture(), m_selectedEntity->GetPosition(),
												m_selectedEntity->GetSize() + (fm::vec2(6, 6) * outlineScale),
												m_selectedEntity->GetRotation(), fm::vec4(1, 1, 0, 1));
			}
		}
		ImGui::EndChild();
	}
	ImGui::End();

	m_lastFrameMousePosition = IMToFM(ImGui::GetMousePos());
}

void ViewportLayer::FPSCounter(f64 dt)
{
	m_frameTimes[m_currentFrameTimeIndex] = dt;
	m_currentFrameTimeIndex = (m_currentFrameTimeIndex + 1) % FRAMETIME_COUNT;
	f64 averageFrameTime = 0;
	for (u_size i = 0; i < FRAMETIME_COUNT; i++)
	{
		averageFrameTime += m_frameTimes[i];
	}
	averageFrameTime /= FRAMETIME_COUNT;
	ImGui::Text("FPS / FrameTime: %.0f / %f", 1 / averageFrameTime, averageFrameTime);
}

bool ViewportLayer::CameraController()
{
	if (!ImGui::IsWindowHovered())
		return false;

	bool returnValue = false;
	DE::Camera* camera = DE::Renderer::GetCamera();

	//Camera mover
	if (ImGui::IsMouseDown(ImGuiMouseButton_Middle))
	{
		const fm::vec2 mousePosition = IMToFM(ImGui::GetMousePos());
		fm::vec2 mouseDelta = m_lastFrameMousePosition - mousePosition;
		mouseDelta /= camera->GetZoom();
		camera->SetPosition(camera->GetPosition() + mouseDelta);
		returnValue = true;
	}

	ImGuiIO& io = ImGui::GetIO();

	if (io.MouseWheel != 0.0f)
	{
		f64 scrollAmount = io.MouseWheel * 0.1;
		camera->SetZoom(camera->GetZoom() + scrollAmount);
		returnValue = true;
	}

	return returnValue;
}

void ViewportLayer::EntitySelector()
{
	if (!ImGui::IsWindowHovered())
		return;

	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		if (DE::Engine::GetWorld())
		{
			const fm::vec2 mousePosition = IMToFM(ImGui::GetMousePos());
			DE::Entity* selectedEntity = DE::Renderer::GetEntityAtPointSlow(mousePosition - m_position);

			SetSelectedEntity(selectedEntity);
		}
	}

	if (m_selectedEntity != nullptr)
	{
		if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
		{
			const fm::vec2 mousePosition = IMToFM(ImGui::GetMousePos());
			DE::Camera* camera = DE::Renderer::GetCamera();
			fm::vec2 mouseDelta = m_lastFrameMousePosition - mousePosition;
			mouseDelta /= camera->GetZoom();
			m_selectedEntity->SetPosition(
				m_selectedEntity->GetPosition() - mouseDelta);
		}
	}
}

void ViewportLayer::SetSelectedEntity(DE::Entity* entity)
{
	if (entity)
	{
		if (entity != m_selectedEntity)
			Log(DE::LogType::Info, "Selected entity %s", entity->GetName().c_str());

		if (!Editor::LayerExists<InspectorLayer>())
			Editor::CreateLayer<InspectorLayer>();
	}

	m_selectedEntity = entity;
}

#endif
