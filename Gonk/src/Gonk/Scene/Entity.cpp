#include "gkpch.h"
#include "Entity.h"

namespace Gonk {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{

	}

}
