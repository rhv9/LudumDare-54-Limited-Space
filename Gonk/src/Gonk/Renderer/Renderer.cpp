#include "gkpch.h"

#include "Renderer.h"
#include "Gonk/Renderer/RendererCommand.h"

namespace Gonk {

    void Renderer::BeginScene()
    {
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        RendererCommand::DrawIndexed(vertexArray);
    }

}