#include "gkpch.h"

#include "Camera.h"
#include <glm/common.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace Gonk {

	OrthographicCamera::OrthographicCamera(glm::mat4& view)
	{
		m_Projection = glm::ortho(-1, 1, -1, 1);
		m_View = view;
	}

}