#pragma once
#include <Gonk.h>
#include "Entity.h"

using namespace Gonk;

class Player : public Entity 
{
public:
	Player();

	virtual void OnUpdate(Timestep ts) override;
	virtual void OnEvent(Event& e) override;

	virtual int GetType() const override { return Entity::Player; }

private:
	int m_CurrentAnimation;
	float m_TimeAnimation = 15.0f;
	Timestep m_TimePassed = 0.0f;

	float m_MoveSpeed = 32.0f;
	bool m_Moving = false;


};