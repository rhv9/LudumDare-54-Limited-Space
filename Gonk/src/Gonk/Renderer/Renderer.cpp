#include "gkpch.h"

#include "Renderer.h"
#include "Gonk/Renderer/RendererCommand.h"
#include "Gonk/Renderer/Renderer2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Gonk {

    Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

    void Renderer::Init()
    {
        GK_PROFILE_FUNCTION();

        RendererCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RendererCommand::OnWindowResize(width, height);
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjection();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        vertexArray->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UniformMat4("u_ViewProjectionMatrix", s_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UniformMat4("u_Transform", transform);
        RendererCommand::DrawIndexed(vertexArray);
    }

    void Renderer::Shutdown()
    {
        RendererCommand::Shutdown();
        Renderer2D::Shutdown();
    }

}