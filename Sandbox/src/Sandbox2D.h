#pragma once

#include <Gonk.h>

class Sandbox2DLayer : public Gonk::Layer
{
public:
	Sandbox2DLayer() : Layer("Sandbox2D") {}

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Gonk::Timestep ts) override;
	virtual void OnEvent(Gonk::Event& event) override;

	virtual void OnImGuiRender() override;
private:
	glm::vec4 m_Col = {0.8f, 0.2f, 0.2f, 1.0f};
	Gonk::Ref<Gonk::Texture> m_Texture;

	Gonk::OrthographicCameraController m_CameraController{1280.0f / 720.0f};
};