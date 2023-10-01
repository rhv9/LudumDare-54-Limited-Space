#include "Player.h"
#include "Game.h"

Player::Player()
{
	m_Animation.resize(4);
	m_Animation[EntityGlobal::UP] = SubTexture2D::CreateMulti(Game::SpriteSheet, { 0.0f, 0.0f }, { Game::SPRITE_SIZE, Game::SPRITE_SIZE }, { 4, 1 });
}

void Player::OnUpdate(Timestep ts)
{
	std::vector<Ref<SubTexture2D>>& anim = m_Animation[m_CurrentAnimation];
	const Ref<SubTexture2D>& subTexture = anim[(int)(Game::TimePassed * m_TimeAnimation) % anim.size()];

	Renderer2D::DrawQuad(m_Position, { subTexture->GetWidth(), subTexture->GetHeight() }, subTexture);
}

void Player::OnEvent(Event& e)
{
}
