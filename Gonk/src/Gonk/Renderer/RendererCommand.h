#pragma once
#include <glm/glm.hpp>

#include "Gonk/Renderer/RendererAPI.h"

namespace Gonk {

	class RendererCommand
	{
	public:

		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetColour(const glm::vec4& colour)
		{
			s_RendererAPI->SetClearColour(colour);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

		inline static void OnWindowResize(uint32_t width, uint32_t height)
		{
			s_RendererAPI->OnWindowResize(width, height);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}
