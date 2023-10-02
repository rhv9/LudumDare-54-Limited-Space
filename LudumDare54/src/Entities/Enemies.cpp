#include "Enemies.h"
#include "Entities/Projectile.h"
#include "Game.h"

EnemySoldier::EnemySoldier()
	: m_CurrentAnimation(-1)
{
}

void EnemySoldier::OnUpdate(Timestep ts)
{
	// Update
	glm::vec2 posMove {0.0f, 0.0f};


	TestLevel* tl = (TestLevel*)Game::m_Level;
	auto pos = tl->m_Player.GetPos();
	
	float xMove = std::min(m_MoveSpeed * ts, std::abs(((m_Position.x - pos.x) / 5.0f) * ts));
	float yMove = std::min(m_MoveSpeed * ts, std::abs(((m_Position.y - pos.y) / 5.0f) * ts));

	if (m_Position.x < pos.x)
	{
		posMove.x += xMove;
	}
	else if (m_Position.x > pos.x)
	{
		posMove.x -= xMove;
	}

	if (m_Position.y < pos.y)
	{
		posMove.y += yMove;
	}
	else if (m_Position.y > pos.y)
	{
		posMove.y -= yMove;
	}


	m_Moving = !(posMove.x == 0.0f && posMove.y == 0.0f);

	if (m_Moving)
		m_TimePassed += ts;
	else
		m_TimePassed = 0.0f;


	if ((int)m_TimePassed % 5)
	{
		tl->AddProjectile(m_Position, pos);
	}

	Move(posMove);

	// Rendering

	std::vector<Ref<SubTexture2D>> anim = Sprite::GetGif(Sprite::Gif::EnemySoldierUp);
	const Ref<SubTexture2D>& subTexture = anim[(int)(0.99999f + m_TimePassed * m_TimeAnimation) % anim.size()];
	Renderer2D::DrawQuad(m_Position, subTexture->GetSize(), subTexture, 1.0f, { 1.0f, 1.0f, 1.0f, 1.0f });
}

void EnemySoldier::OnEvent(Event& e)
{
}
