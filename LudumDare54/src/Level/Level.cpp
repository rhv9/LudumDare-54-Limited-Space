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
	for (int y = 0; y < m_Height; y++)
	{
		for (int x = 0; x < m_Width; x++)
		{
			const glm::vec3 pos = { (int)(x * Sprite::SIZE.x), (int)(y * Sprite::SIZE.x), 0.0f };
			m_Map[y * m_Width + x]->OnUpdate(pos, ts);
		}
	}
	if (Input::IsKeyPressed(Key::SPACE))
	{
		PresetTile::GrassTile->OnUpdate({ 0.0f, 0.0f, 0.0f }, ts);
		GK_CORE_TRACE("Rendering Tile");
	}

	static Ref<Texture2D> tex = Texture2D::Create("assets/textures/spritesheet.png");
	static auto grassTex = SubTexture2D::CreateFromCoords(tex, { 0.0f, 4.0f }, Sprite::SIZE);
	static auto playerSet = SubTexture2D::CreateMulti(tex, { 0.0f, 0.0f }, Sprite::SIZE, { 4, 1 });

	Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, Sprite::SIZE, tex);
	Renderer2D::DrawQuad({ Sprite::SIZE, 0.0f }, Sprite::SIZE, grassTex);
	Renderer2D::DrawQuad({ -Sprite::SIZE, 0.0f }, Sprite::SIZE, playerSet[(int)(Game::s_TimePassed* 10.0f) % 4]);

	Renderer2D::DrawQuad({ Sprite::SIZE * 3.0f, 0.0f }, Sprite::SIZE, Sprite::GetTex(Sprite::Tex::Spritesheet));
	Renderer2D::DrawQuad({ Sprite::SIZE * 4.0f, 0.0f },Sprite::SIZE, Sprite::GetGif(Sprite::Gif::PlayerUp)[0]);
	Renderer2D::DrawQuad({ Sprite::SIZE * 2.0f, 0.0f }, Sprite::SIZE, Sprite::GetSub(Sprite::Sub::Grass));

	m_Player.OnUpdate(ts);
}

void TestLevel::OnEvent(Event& e)
{
	m_Player.OnEvent(e);
}


