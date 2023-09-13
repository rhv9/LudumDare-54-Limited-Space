#include "gkpch.h"

#include "Camera.h"
#include <glm/common.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Gonk {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top)), m_ViewMatrix(1.0f)
	{
		GK_PROFILE_FUNCTION();

		RecalculateProjectionMatrix();
	}

	void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top)
	{
		GK_PROFILE_FUNCTION();

		m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateProjectionMatrix()
	{
		GK_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), {0.0f, 0.0f, 1.0f});
		m_ViewMatrix = glm::inverse(transform);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}