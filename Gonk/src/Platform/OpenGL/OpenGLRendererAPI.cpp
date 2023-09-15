#include "gkpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Gonk {

	void OpenGLRendererAPI::Init()
	{
		GK_PROFILE_FUNCTION();

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetClearColour(const glm::vec4& colour)
	{
		glClearColor(colour.r, colour.g, colour.b, colour.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) const
	{
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::OnWindowResize(uint32_t width, uint32_t height)
	{
		glViewport(0, 0, width, height);
	}

	void OpenGLRendererAPI::Shutdown()
	{
		// TODO: Don't know if I should be doing stuff here
	}

}