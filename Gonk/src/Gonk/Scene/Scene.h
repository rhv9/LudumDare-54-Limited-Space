#pragma once

#include "entt.hpp"
#include "Gonk/Core/Timestep.h"

namespace Gonk {

	class Scene
	{
	public:
		Scene();
		~Scene();

		// temp
		entt::registry& Reg() { return m_Registry; }

		entt::entity CreateEntity();

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
	};

}