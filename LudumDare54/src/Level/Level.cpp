#include "Level.h"
#include <Gonk.h>

#include "Game.h"
using namespace Gonk;

TestLevel::TestLevel()
{
	Game::s_CameraController.SetZoomLevel(80);

	m_Width = 10;
	m_Height = 10;
	m_Player.SetPos({ -32.0f, 0.0f, 0.8f });

	m_Map = new Tile*[m_Width * m_Height];

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
	
	glm::vec2 pos = Game::s_CameraController.GetPosition();
	float zoom = Game::s_CameraController.GetZoomLevel();

	int xStart = (int)((pos.x - Game::WIDTH / 2.0f)) >> 4;
	int yStart = (int)((pos.y - Game::HEIGHT / 2.0f)) >> 4;

	int xEnd = xStart + (int)(Game::WIDTH >> 4);
	int yEnd = yStart + (int)(Game::HEIGHT >> 4);

	xStart += 32 - 1;
	xEnd   -= 30 - 1;

	yStart += 19 - 2;
	yEnd   -= 17 - 1;
	//Game::ImGuiPrint("(xStart, yStart) = ({}, {})", xStart, yStart);
	//Game::ImGuiPrint("(xEnd, yEnd) = ({}, {})", xEnd, yEnd);

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
				PresetTile::WaterTile->OnUpdate(pos, ts);

		}
	}
	if (Input::IsKeyPressed(Key::SPACE))
	{
		Game::ImGuiPrint("Rendering Tile");
	}

	m_Player.OnUpdate(ts);
}

void TestLevel::OnEvent(Event& e)
{
	m_Player.OnEvent(e);
}

bool TestLevel::InMapBounds(int x, int y) const
{
	return !(x < 0 || x >= m_Width || y < 0 || y >= m_Height);
}


