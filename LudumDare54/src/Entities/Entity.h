#pragma once

#include <Gonk.h>

using namespace Gonk;

struct EntityGlobal
{
	static const int UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3;
};

class Entity
{
public:
	Entity() = default;

	virtual void OnUpdate(Timestep ts) = 0;
	virtual void OnEvent(Event& e) = 0;

	const glm::vec3& GetPos() { return m_Position; }
	void SetPos(const glm::vec3& pos) { m_Position = pos; }

protected:
	glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };

};