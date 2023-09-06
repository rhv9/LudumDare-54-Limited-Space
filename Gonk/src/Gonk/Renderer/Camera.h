#pragma once

namespace Gonk {

	class Camera 
	{
	public:

	private:

	};

	class OrthographicCamera : public Camera
	{
	public:

		OrthographicCamera(glm::mat4& view);

		glm::mat4 GetVP() const { return m_Projection * m_View; }

	private:
		glm::mat4 m_View;
		glm::mat4 m_Projection;
	};

}