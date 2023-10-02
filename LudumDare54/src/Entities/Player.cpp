#include "Player.h"
#include "Game.h"
#include "Sprite.h"

Player::Player()
	: m_CurrentAnimation(-1)
{
}

void Player::OnUpdate(Timestep ts)
{
	// Update
	glm::vec2 posMove {0.0f, 0.0f};

	if (Input::IsKeyPressed(Key::W))
	{
		posMove.y += m_MoveSpeed * ts;
	}
	if (Input::IsKeyPressed(Key::S))
	{
		posMove.y -= m_MoveSpeed * ts;
	}
	if (Input::IsKeyPressed(Key::A))
	{
		posMove.x -= m_MoveSpeed * ts;
	}
	if (Input::IsKeyPressed(Key::D))
	{
		posMove.x += m_MoveSpeed * ts;
	}

	m_Moving = !(posMove.x == 0.0f && posMove.y == 0.0f);

	if (m_Moving)
		m_TimePassed += ts;
	else
		m_TimePassed = 0.0f;

	Move(posMove);
	CollisionBox box1 = { 0.0f, 0.0f, 16.0f, 16.0f };
	CollisionBox box2 = { m_Position.x, m_Position.y, 16.0f, 16.0f };





	Game::s_CameraController.SetPosition({ m_Position.x, m_Position.y });

	// Rendering

	std::vector<Ref<SubTexture2D>> anim = Sprite::GetGif(Sprite::Gif::PlayerUp);
	const Ref<SubTexture2D>& subTexture = anim[(int)(0.99999f + m_TimePassed * m_TimeAnimation) % anim.size()];
	Renderer2D::DrawQuad(m_Position, subTexture->GetSize(), subTexture, 1.0f, {1.0f, 1.0f, 1.0f, 0.5f});

	if (box1.Collides(box2))
	{
		box1.Render({ 0.2f, 1.0f, 0.2f, 1.0f});
		box2.Render({ 0.2f, 1.0f, 0.2f, 1.0f});
	}
	else
	{
		box1.CollisionShape::Render();
		box2.CollisionShape::Render();
	}
}

void Player::OnEvent(Event& e)
{
}
