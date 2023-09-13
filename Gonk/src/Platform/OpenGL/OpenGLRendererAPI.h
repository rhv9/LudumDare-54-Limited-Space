#pragma once

#include "Gonk/Renderer/RendererAPI.h"

namespace Gonk {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetClearColour(const glm::vec4& colour) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) const override;

		virtual void OnWindowResize(uint32_t width, uint32_t height) override;

		virtual void Shutdown() override;
	};

}