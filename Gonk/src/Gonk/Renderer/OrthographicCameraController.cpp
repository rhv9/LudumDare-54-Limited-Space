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
		m_Position = pos;
		m_Camera.SetPosition({ m_Position , 0.0f});
	}

	void OrthographicCameraController::OnResize(uint32_t width, uint32_t height)
	{
		SetAspectRatio((float)width / (float)height);
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		GK_PROFILE_FUNCTION();

		if (Gonk::Input::IsKeyPressed(Gonk::Key::W))
			m_Position.y += m_ZoomLevel * ts;
		if (Gonk::Input::IsKeyPressed(Gonk::Key::S))
			m_Position.y -= m_ZoomLevel * ts;
		if (Gonk::Input::IsKeyPressed(Gonk::Key::D))
			m_Position.x += m_ZoomLevel * ts;
		if (Gonk::Input::IsKeyPressed(Gonk::Key::A))
			m_Position.x -= m_ZoomLevel * ts;

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

		if (!m_EnabledScrollZoom) return false;

		SetZoomLevel(m_ZoomLevel + -e.GetYOffset() * 2.0f);
		return false;
	}
	
	bool OrthographicCameraController::OnWindowResizeCallback(WindowResizeEvent& e)
	{
		GK_PROFILE_FUNCTION();

		SetAspectRatio((float)e.getWidth() / (float)e.getHeight());
		return false;
	}

}