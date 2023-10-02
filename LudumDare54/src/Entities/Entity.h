#pragma once

#include <Gonk.h>
#include "Collision.h"

using namespace Gonk;



class Entity
{
public:

	static const int Player = 0;
	static const int EnemySoldier = 1;
	static const int Projectile = 2;


	Entity() = default;

	virtual void OnUpdate(Timestep ts) {};
	virtual void OnEvent(Event& e) {};

	virtual void Move(const glm::vec2& pos);

	const glm::vec3& GetPos() { return m_Position; }
	void SetPos(const glm::vec3& pos) { m_Position = pos; }

	virtual int GetType() const = 0;

protected:
	glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };

};