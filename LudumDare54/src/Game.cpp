#include <Gonk.h>
#include <Gonk/Core/EntryPoint.h>

#include <imgui/imgui.h>
#include "Game.h"

#include "Sprite.h"
#include "Level/Tile.h"

using namespace Gonk;

OrthographicCameraController Game::s_CameraController = { (float)Game::WIDTH / (float)Game::HEIGHT};
Timestep Game::s_TimePassed = 0.0f;

TestLevel* forestLevel;

Game::Game()
	: Layer("Game Layer")
{
	Sprite::Init();
	PresetTile::Init();

	// init levels
	forestLevel = new TestLevel();
	m_Level = forestLevel;
}

void Game::OnAttach()
{
}

void Game::OnDetach()
{
}

static float timestep = 0.0f;
void Game::OnUpdate(Timestep ts)
{
	timestep = ts.GetMilliSeconds();
	Game::s_TimePassed += ts;

	Renderer2D::ResetStats();

	RendererCommand::Clear();
	RendererCommand::SetColour({ 0.5f, 0.5f, 0.5f, 1.0f });

	Renderer2D::BeginScene(s_CameraController.GetCamera());

	if (m_Level)
		m_Level->OnUpdate(ts);
	else
		GK_ERROR("No level is set!");

	Renderer2D::EndScene(); 
}

void Game::OnEvent(Event& e)
{
	s_CameraController.OnEvent(e);

	m_Level->OnEvent(e);
}

void Game::OnImGuiRender()
{
	ImGui::Begin("Test");

	auto stats = Gonk::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("	FrameTime: %0.2fms (%f fps)", timestep, 1000.0f / timestep);
	ImGui::Text("	Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("	Quads: %d", stats.QuadCount);
	ImGui::Text("	Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("	Indices: %d", stats.GetTotalIndexCount());
	ImGui::Text(std::format(" timestep count: {}", (float)Game::s_TimePassed).c_str());

	ImGui::Text("Camera Info:");
	ImGui::Text(std::format("  Zoom Level: {}", s_CameraController.GetZoomLevel()).c_str());
	ImGui::Text("  Position: %3.2f, %3.2f", *(float*)&s_CameraController, *((float*)&s_CameraController + 1));

	ImGui::End();
}


GameApplication::GameApplication()
{
	m_GameLayer = new Game();
	PushLayer(m_GameLayer);
}

GameApplication::~GameApplication()
{
}

Gonk::Application* Gonk::CreateApplication() 
{
	return new GameApplication();
}