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
	int m_CurrentAnimation = EntityGlobal::UP;
	std::vector<std::vector<Ref<SubTexture2D>>> m_Animation;
	float m_TimeAnimation = 5.0f;
};