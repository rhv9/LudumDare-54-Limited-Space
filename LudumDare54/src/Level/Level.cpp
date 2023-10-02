#include "Level.h"
#include <Gonk.h>

#include "Game.h"
#include "Random.h"

#include "Entities/Enemies.h"
#include "Entities/Projectile.h"
using namespace Gonk;

EnemySoldier es;

TestLevel::TestLevel()
{
	Game::s_CameraController.SetZoomLevel(80);
	Game::s_CameraController.SetScrollZoomable(false);

	m_Entities.reserve(10000);

	m_Width = 25;
	m_Height = 25;
	m_Player.SetPos({ 32.0f, 32.0f, 0.8f });

	m_Map = new Tile*[m_Width * m_Height];

	es.SetPos({ 50.0f, 50.0f, 0.0f });

	for (int y = 0; y < m_Height; y++)
	{
		for (int x = 0; x < m_Width; x++)
		{
			m_Map[y * m_Width + x] = PresetTile::GrassTile;
		}
	}

}

TestLevel::~TestLevel()
{
	delete[] m_Map;
}

void TestLevel::OnUpdate(Timestep ts)
{
	
	glm::vec2 cameraPos = Game::s_CameraController.GetPosition();
	float zoom = Game::s_CameraController.GetZoomLevel();

	int xStart = (int)((cameraPos.x - Game::WIDTH / 2.0f)) >> 4;
	int yStart = (int)((cameraPos.y - Game::HEIGHT / 2.0f)) >> 4;

	int xEnd = xStart + (int)(Game::WIDTH >> 4);
	int yEnd = yStart + (int)(Game::HEIGHT >> 4);

	// I don't know how to scale with zoom level so heres my solution...
	xStart += 32 - 1;
	xEnd   -= 30 - 1;

	yStart += 19 - 2;
	yEnd   -= 17 - 1;
	//Game::ImGuiPrint("(xStart, yStart) = ({}, {})", xStart, yStart);
	//Game::ImGuiPrint("(xEnd, yEnd) = ({}, {})", xEnd, yEnd);
	

	if (((int)(Game::s_TimePassed * 144.0f) % 20) == 0)
	{
		EnemySoldier* soldier = new EnemySoldier;
		soldier->SetPos({ Random::Float() * m_Width * 16, Random::Float() * m_Height * 16, 0.2f});
		AddEntity(soldier);
	}


	for (int y = yStart; y < yEnd; y++)
	{
		for (int x = xStart; x < xEnd; x++)
		{
			const glm::vec3 pos = { (int)(x * Sprite::SIZE.x), (int)(y * Sprite::SIZE.x), 0.0f };
			if (InMapBounds(x, y))
			{
				m_Map[y * m_Width + x]->OnUpdate(pos, ts);
			}
			else
			{
				PresetTile::WaterTile->OnUpdate(pos, ts);
			}

		}
	}
	if (Input::IsKeyPressed(Key::SPACE))
	{
		Game::ImGuiPrint("Rendering Tile");
	}

	if (Input::IsMouseButtonPressed(MouseButton::LEFT))
	{
		auto [xOffset, yOffset] = Game::GetMousePositionInWorld();
		Game::ImGuiPrint("{}, {}", xOffset, yOffset);

		auto sprite = Sprite::GetSub(Sprite::Sub::CollisionBox);
		Renderer2D::DrawQuad({ xOffset, yOffset, 0.3f }, sprite->GetSize(), sprite);
	}

	Game::ImGuiPrint("Entity Count: {}", m_Entities.size());
	for (Entity* entity : m_Entities)
	{
		entity->OnUpdate(ts);
	}

	es.OnUpdate(ts);
	m_Player.OnUpdate(ts);
}

void TestLevel::OnEvent(Event& e)
{
	m_Player.OnEvent(e);

	if (e.GetEventType() == EventType::MouseButtonPressed)
	{
		auto [x, y] = Game::GetMousePositionInWorld();


		glm::vec2 playerPos = m_Player.GetPos();
		glm::vec2 clickPos = { x, y };

		Projectile* es = new Projectile;
		auto length = glm::length(playerPos - clickPos);

		auto standardise = (-playerPos + clickPos) / length;


		es->SetPos({ playerPos, 0.2f });
		es->m_Move = standardise;
		AddEntity(es);
	}
}

void TestLevel::AddProjectile(const glm::vec2 PlayerPos, const glm::vec2 ClickPos)
{
	glm::vec2 playerPos = PlayerPos;
	glm::vec2 clickPos = ClickPos;

	Projectile* p = new Projectile;
	auto length = glm::length(playerPos - clickPos);

	auto standardise = (-playerPos + clickPos) / length;

	p->SetPos({ playerPos, 0.2f });
	p->m_Move = standardise;
	AddEntity(p);
}

void TestLevel::AddEntity(Entity* e)
{
	m_Entities.push_back(e);
}

bool TestLevel::InMapBounds(int x, int y) const
{
	return !(x < 0 || x >= m_Width || y < 0 || y >= m_Height);
}


