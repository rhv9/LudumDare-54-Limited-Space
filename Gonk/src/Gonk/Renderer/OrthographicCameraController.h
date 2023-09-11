#pragma once

#include "Gonk/Core/Timestep.h"
#include "Gonk/Events/ApplicationEvent.h"
#include "Gonk/Events/MouseEvent.h"

#include "Gonk/Renderer/Camera.h"

namespace Gonk {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(const float aspectRatio, const float zoomLevel = 1.0f);

		void SetPosition(const glm::vec2& pos);
		void SetAspectRatio(const float aspectRatio);
		void SetRotation(const float rotation) { m_Rotation = rotation; }

		OrthographicCamera& GetCamera(){ return m_Camera; }

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
	private:
		bool OnMouseScrollCallback(MouseScrolledEvent& e);
		bool OnWindowResizeCallback(WindowResizeEvent& e);


	private:
		float m_AspectRatio, m_ZoomLevel;

		OrthographicCamera m_Camera;

		glm::vec2 m_Position = { 0.0f, 0.0f };
		float m_Rotation = 0.0f;

		float m_CameraSpeed = 1.0f, m_RotationSpeed = 360.0f;

	};

}