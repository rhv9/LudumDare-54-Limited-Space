#include "gkpch.h"
#include "Sandbox2D.h"
#include <Gonk.h>

#include <imgui/imgui.h>
#include "Platform/OpenGL/OpenGLShader.h"

#include <chrono>


void Sandbox2DLayer::OnAttach()
{
	GK_PROFILE_FUNCTION();

	m_CheckerboardTexture = Gonk::Texture2D::Create("assets/textures/Checkerboard.png");
	m_LogoTexture = Gonk::Texture2D::Create("assets/textures/ChernoLogo.png");
}

void Sandbox2DLayer::OnDetach()
{
	GK_PROFILE_FUNCTION();

}

glm::vec3 redPos { 0.0f, 0.0f, -0.0f } ;
glm::vec3 greenPos { -1.0f, -1.0f, -0.2f };
float rotation = 0.0f;
float autoRotate = 0.0f;

void Sandbox2DLayer::OnUpdate(Gonk::Timestep ts)
{
	GK_PROFILE_FUNCTION();

	// update
	m_CameraController.OnUpdate(ts);

	// Render
	{
		GK_PROFILE_SCOPE("Renderer Prep");
		Gonk::RendererCommand::SetColour(glm::vec4{0.2f});
		Gonk::RendererCommand::Clear();
	}
	
	
	autoRotate += 10.0f;

	Gonk::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Gonk::Renderer2D::DrawQuad(redPos, {1.0f, 1.0f }, { 0.8f, 0.2f, 0.2f, 1.0f });
	Gonk::Renderer2D::DrawQuad(greenPos, {2.0f, 2.0f}, { 0.2f, 0.8f, 0.2f, 1.0f });
	Gonk::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 10.0f, {1.0f, 0.5f, 0.5f, 1.0f});
	Gonk::Renderer2D::DrawRotatedQuad({ 2.0f, 2.0f, 0.0f }, { 1.0f, 1.0f }, autoRotate, {0.0f, 1.0f, 1.0f, 1.0f});
	Gonk::Renderer2D::DrawQuad({1.0f, 1.0f, 0.1f}, {1.0f, 1.0f}, m_LogoTexture, 3.0f, { 0.5f, 1.0f, 0.5f, 1.0f });

	Gonk::Renderer2D::EndScene();
}

void Sandbox2DLayer::OnEvent(Gonk::Event& e)
{
	m_CameraController.OnEvent(e);
}

void Sandbox2DLayer::OnImGuiRender()
{
	GK_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Col", &m_Col[0]);
	ImGui::DragFloat3("Red Pos", &redPos[0], 0.05f, -1.0f, 1.0f);
	ImGui::DragFloat3("Green Pos", &greenPos[0], 0.05f, -1.0f, 1.0f);
	ImGui::DragFloat("Rotation", &rotation, 0.5f, -360.0f, 360.0f);
	ImGui::End();
}
