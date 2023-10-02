#pragma once

#include <Gonk.h>
#include "Collision.h"

using namespace Gonk;

class Entity
{
public:
	Entity() = default;

	virtual void OnUpdate(Timestep ts) = 0;
	virtual void OnEvent(Event& e) = 0;

	virtual void Move(const glm::vec2& pos);

	const glm::vec3& GetPos() { return m_Position; }
	void SetPos(const glm::vec3& pos) { m_Position = pos; }

protected:
	glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };

};