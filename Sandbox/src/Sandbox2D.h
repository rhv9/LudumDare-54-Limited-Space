#pragma once

#include <Gonk.h>

#include "ParticleSystem.h"

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
	Gonk::Ref<Gonk::Texture2D> m_CheckerboardTexture, m_LogoTexture;

	Gonk::OrthographicCameraController m_CameraController{1280.0f / 720.0f};

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;

	Gonk::Ref<Gonk::Texture2D> m_Spritesheet;
	Gonk::Ref<Gonk::SubTexture2D> m_Barrel, m_Tree;
	Gonk::Ref<Gonk::Framebuffer> m_Framebuffer;

	std::unordered_map<char, Gonk::Ref<Gonk::SubTexture2D>> s_TextureMap;
};