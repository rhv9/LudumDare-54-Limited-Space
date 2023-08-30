#pragma once

#include "Gonk/Renderer/RendererAPI.h"

namespace Gonk {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColour(const glm::vec4& colour) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) const override;
	};

}