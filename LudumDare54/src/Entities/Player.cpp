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

	Game::s_CameraController.SetPosition({ m_Position.x, m_Position.y });

	// Rendering

	std::vector<Ref<SubTexture2D>> anim = Sprite::GetGif(Sprite::Gif::PlayerUp);
	const Ref<SubTexture2D>& subTexture = anim[(int)(0.99999f + m_TimePassed * m_TimeAnimation) % anim.size()];
	Renderer2D::DrawQuad(m_Position, subTexture->GetSize(), subTexture, 1.0f, {1.0f, 1.0f, 1.0f, 0.5f});
}

void Player::OnEvent(Event& e)
{
}
