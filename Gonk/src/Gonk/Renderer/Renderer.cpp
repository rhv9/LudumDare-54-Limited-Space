#include "gkpch.h"

#include "Renderer.h"
#include "Gonk/Renderer/RendererCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Gonk {

    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjection();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        vertexArray->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UniformMat4("u_ViewProjectionMatrix", m_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UniformMat4("u_Transform", transform);
        RendererCommand::DrawIndexed(vertexArray);
    }

}