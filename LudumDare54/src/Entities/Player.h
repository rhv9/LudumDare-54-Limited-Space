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

private:
	int m_CurrentAnimation;
	float m_TimeAnimation = 15.0f;

	float m_MoveSpeed = 32.0f;
	bool m_Moving = false;
	Timestep m_TimePassed = 0.0f;
};