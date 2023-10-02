#pragma once
#include "Entities/Entity.h"

class Projectile : public Entity
{
public:
	Projectile();

	virtual void OnUpdate(Timestep ts) override;
	virtual void OnEvent(Event& e) override;

	virtual int GetType() const override { return Entity::Projectile; }

	glm::vec2 m_Move = { 0.0f, 0.0f };
private:
	float m_Lifetime = 8;

	float m_MoveSpeed = 0.6f;
	bool m_Moving = false;
	Timestep m_TimePassed = 0.0f;


};