#include "gkpch.h"
#include "Entity.h"

void Entity::Move(const glm::vec2& pos)
{
	m_Position += glm::vec3{ pos, 0.0f };
}
