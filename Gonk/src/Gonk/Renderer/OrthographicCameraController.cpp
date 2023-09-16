#include "gkpch.h"
#include "OrthographicCameraController.h"

#include "Gonk/Input/Input.h"
#include "Gonk/Input/KeyCodes.h"

#include "Gonk/Core/Application.h"

namespace Gonk {


	OrthographicCameraController::OrthographicCameraController(const float aspectRatio, const float zoomLevel)
		: m_AspectRatio(aspectRatio), m_ZoomLevel(zoomLevel), m_Bounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }), m_Camera(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top)
	{
	}

	void OrthographicCameraController::SetPosition(const glm::vec2& pos)
	{
		m_Camera.SetPosition(glm::vec3{pos, 0.0f});
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		GK_PROFILE_FUNCTION();

		if (Gonk::Input::IsKeyPressed(GK_KEY_W))
			m_Position.y += m_ZoomLevel * ts;
		if (Gonk::Input::IsKeyPressed(GK_KEY_S))
			m_Position.y -= m_ZoomLevel * ts;
		if (Gonk::Input::IsKeyPressed(GK_KEY_D))
			m_Position.x += m_ZoomLevel * ts;
		if (Gonk::Input::IsKeyPressed(GK_KEY_A))
			m_Position.x -= m_ZoomLevel * ts;

		if (Gonk::Input::IsKeyPressed(GK_KEY_LEFT))
			m_Rotation -= m_RotationSpeed * ts;
		if (Gonk::Input::IsKeyPressed(GK_KEY_RIGHT))
			m_Rotation += m_RotationSpeed * ts;

		m_Camera.SetPosition(glm::vec3{m_Position, 0.0f});
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		GK_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&OrthographicCameraController::OnMouseScrollCallback, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&OrthographicCameraController::OnWindowResizeCallback, this, std::placeholders::_1));

	}

	void OrthographicCameraController::CalculateView()
	{
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		m_Camera.SetProjectionMatrix(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}

	bool OrthographicCameraController::OnMouseScrollCallback(MouseScrolledEvent& e)
	{
		GK_PROFILE_FUNCTION();

		SetZoomLevel(m_ZoomLevel + -e.GetYOffset() * 0.5f);
		return false;
	}
	
	bool OrthographicCameraController::OnWindowResizeCallback(WindowResizeEvent& e)
	{
		GK_PROFILE_FUNCTION();

		SetAspectRatio((float)e.getWidth() / (float)e.getHeight());
		return false;
	}

}