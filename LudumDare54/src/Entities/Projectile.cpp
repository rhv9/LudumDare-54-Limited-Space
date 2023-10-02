#include "Enemies.h"
#include "Projectile.h"

#include "Sprite.h"
#include "Game.h"

Projectile::Projectile()
{
}

void Projectile::OnUpdate(Timestep ts)
{
	// Update
	glm::vec2 posMove {0.0f, 0.0f};

	TestLevel* tl = (TestLevel*)Game::m_Level;
	auto pos = tl->m_Player.GetPos();

	m_Lifetime -= (float)ts;

	if (m_Lifetime <= 0.0f)
	{
		return;
	}


	Move(m_Move * m_MoveSpeed);
	
	// do collisions

	// Rendering

	auto sprite = Sprite::GetSub(Sprite::Sub::Projectile);
	Renderer2D::DrawQuad(m_Position, sprite->GetSize(), sprite);
}

void Projectile::OnEvent(Event& e)
{
}
