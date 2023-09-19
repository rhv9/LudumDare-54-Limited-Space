#pragma once

#include "entt.hpp"
#include "Gonk/Core/Timestep.h"

namespace Gonk {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		// temp
		entt::registry& Reg() { return m_Registry; }

		Entity CreateEntity(const std::string& name = std::string("Entity"));

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;

		friend class Entity;
	};

}