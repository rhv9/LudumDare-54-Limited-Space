#include "gkpch.h"
#include "Scene.h"

#include "Component.h"
#include "Gonk/Renderer/Renderer2D.h"

#include "Entity.h"

namespace Gonk {

    static void DoMaths(const glm::mat4& transform)
    {

    }

    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
    }

    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity e = { m_Registry.create() , this };
        e.AddComponent<TransformComponent>();
        e.AddComponent<TagComponent>(name);
        return e;
    }

    void Scene::OnUpdate(Timestep ts)
    {
        auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity : group)
        {
            auto&& [transform, spriteRenderer] = group.get<TransformComponent, SpriteRendererComponent>(entity);
            
            Renderer2D::DrawQuad(transform, spriteRenderer.Colour);
        }
    }

}