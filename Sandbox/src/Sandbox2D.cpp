#include "gkpch.h"
#include "Sandbox2D.h"
#include <Gonk.h>

#include <imgui/imgui.h>
#include "Platform/OpenGL/OpenGLShader.h"

#include <chrono>

struct ProfileResult
{
	const char* Name;
	float Time;
};

static std::vector<ProfileResult> s_ProfileResults;

template <typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Func(func)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop() 
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		m_Stopped = true;

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		float duration = (float)(end - start) / 1000.0f;

		m_Func({ m_Name, duration });
	}

private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped = false;
	Fn m_Func;
};

void Sandbox2DLayer::OnAttach()
{
	m_Texture = Gonk::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2DLayer::OnDetach()
{
}

void Sandbox2DLayer::OnUpdate(Gonk::Timestep ts)
{
	Timer timer("Sandbox2D::OnUpdate", [&](ProfileResult profileResult) { s_ProfileResults.push_back(profileResult); });

	m_CameraController.OnUpdate(ts);

	Gonk::RendererCommand::SetColour(glm::vec4{0.2f});
	Gonk::RendererCommand::Clear();

	Gonk::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Gonk::Renderer2D::DrawQuad({ 0.0f, 0.2f }, {0.25f, 0.5f}, m_Texture, m_Col);
	Gonk::Renderer2D::DrawQuad({ 1.0f, 2.0f }, {0.5f, 1.5f}, m_Texture, m_Col);
	Gonk::Renderer2D::DrawQuad({ -5.0f, -5.0f }, {10.0f, 10.0f }, m_Texture);
	Gonk::Renderer2D::DrawQuad({ -1.0f, -1.0f }, {0.5f, 0.5f}, {0.2f, 0.2f, 0.8f, 1.0f });

	Gonk::Renderer::EndScene();
}

void Sandbox2DLayer::OnEvent(Gonk::Event& e)
{
	m_CameraController.OnEvent(e);
}

void Sandbox2DLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Col", &m_Col[0]);

	for (auto& result : s_ProfileResults)
	{
		char label[50];
		strcpy(label, result.Name);
		strcat(label, " %.3fms");
		ImGui::Text(label, result.Time);
	}

	s_ProfileResults.clear();

	ImGui::End();
}
