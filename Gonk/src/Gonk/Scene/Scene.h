#pragma once

#include "entt.hpp"
#include "Gonk/Core/Timestep.h"
#include "Component.h"

namespace Gonk {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		// temp
		entt::registry& Reg() { return m_Registry; }

		template<typename T, typename... Args>
		T CreateEntity(const std::string& name, Args&&... args);


		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;

		friend class Entity;
	};

	template<typename T, typename... Args>
	T Scene::CreateEntity(const std::string& name, Args&&... args)
	{
		T e = { m_Registry.create() , this };
		e.AddComponent<TransformComponent>(glm::mat4(1.0f));
		e.AddComponent<TagComponent>(name);
		e.Init(std::forward<Args>(args)...);
		return e;
	}

}