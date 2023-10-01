#include <Gonk.h>
#include <Gonk/Core/EntryPoint.h>

#include <imgui/imgui.h>
#include "Game.h"

using namespace Gonk;

static float timestep = 0.0f;
const int SPRITE_SIZE = 16;

static Ref<SubTexture2D> playerSprite;
std::vector<Ref<SubTexture2D>> textures;

ForestLevel* forestLevel;

GameLayer::GameLayer()
	: Layer("Game Layer"), m_CameraController((float)width / (float)height)
{
	m_CameraController.SetZoomLevel(50);

	Game::SpriteSheet = Texture2D::Create("assets/textures/spritesheet.png");
	playerSprite = SubTexture2D::CreateFromCoords(Game::SpriteSheet, { 0.0f, 0.0f }, { SPRITE_SIZE, SPRITE_SIZE });
	textures = SubTexture2D::CreateMulti(Game::SpriteSheet, { 0.0f, 0.0f }, { SPRITE_SIZE, SPRITE_SIZE }, { 4, 1 });

	// init levels
	forestLevel = new ForestLevel();

	m_Level = forestLevel;
}

void GameLayer::OnAttach()
{
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Timestep ts)
{
	timestep = ts.GetMilliSeconds();
	Game::TimePassed += ts;
	m_CameraController.OnUpdate(ts);

	Renderer2D::ResetStats();
	RendererCommand::Clear();
	RendererCommand::SetColour({ 0.8f, 0.5f, 0.8f, 1.0f });

	Renderer2D::BeginScene(m_CameraController.GetCamera());
	
	m_Level->OnUpdate(ts);

	Renderer2D::EndScene(); 
}

void GameLayer::OnEvent(Event& e)
{
	m_CameraController.OnEvent(e);

	m_Level->OnEvent(e);
}

void GameLayer::OnImGuiRender()
{
	ImGui::Begin("Test");

	auto stats = Gonk::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("	FrameTime: %0.2fms (%f fps)", timestep, 1000.0f / timestep);
	ImGui::Text("	Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("	Quads: %d", stats.QuadCount);
	ImGui::Text("	Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("	Indices: %d", stats.GetTotalIndexCount());

	ImGui::Text("Camera Info:");
	ImGui::Text(std::format("Zoom Level: {}", m_CameraController.GetZoomLevel()).c_str());
	ImGui::Text(std::format("timestep count: {}", (float)Game::TimePassed).c_str());

	ImGui::End();
}

Timestep Game::TimePassed = 0.0f;
Ref<Texture2D> Game::SpriteSheet;


Game::Game()
{
	PushLayer(new GameLayer());
}

Game::~Game()
{
}

Gonk::Application* Gonk::CreateApplication() 
{
	return new Game();
}