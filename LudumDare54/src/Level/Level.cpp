#include "Level.h"
#include <Gonk.h>

using namespace Gonk;

TestLevel::TestLevel()
{
	m_Width = 1;
	m_Height = 1;
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
	for (int y = 0; y < m_Height; y++)
	{
		for (int x = 0; x < m_Width; x++)
		{
			//m_Map[y * m_Width + x]->OnUpdate(glm::vec3{x * Sprite::SPRITE_SIZE, y * Sprite::SPRITE_SIZE, 0.0f}, ts);
		}
	}
	if (Input::IsKeyPressed(Key::SPACE))
	{
		PresetTile::GrassTile->OnUpdate({ 0.0f, 0.0f, 0.0f }, ts);
		GK_CORE_TRACE("Rendering Tile");
	}

	Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, Sprite::GetGif(Sprite::Gif::PlayerUp)[0]->GetSize(), Sprite::GetTex(Sprite::Tex::Spritesheet));
	Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, Sprite::GetGif(Sprite::Gif::PlayerUp)[0]->GetSize(), Sprite::GetGif(Sprite::Gif::PlayerUp)[0]);
	Renderer2D::DrawQuad({ 16.0f, 16.0f, 0.0f }, Sprite::GetSub(Sprite::Sub::Grass)->GetSize(), Sprite::GetSub(Sprite::Sub::Grass));

	m_Player.OnUpdate(ts);
}

void TestLevel::OnEvent(Event& e)
{
	m_Player.OnEvent(e);
}


