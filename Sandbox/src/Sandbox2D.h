#pragma once

#include <Gonk.h>

class Sandbox2DLayer : public Gonk::Layer
{
public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Gonk::Timestep ts) override;
	virtual void OnEvent(Gonk::Event& event) override;

	virtual void OnImGuiRender() override;
private:
	Gonk::Ref<Gonk::VertexArray> m_VertexArray;
	Gonk::Ref<Gonk::Shader> m_FlatShader;

	glm::vec4 m_Col = {0.8f, 0.2f, 0.2f, 1.0f};

	Gonk::OrthographicCameraController m_CameraController{1280.0f / 720.0f};
};