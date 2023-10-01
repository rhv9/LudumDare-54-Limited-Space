#pragma once
#include <Gonk.h>
#include "Sprite.h"

using namespace Gonk;

class Tile 
{
public:
	Tile() = default;
		
	virtual void OnUpdate(const glm::vec3& pos, Timestep ts) = 0;
	virtual void OnEvent(Event& e) = 0;

	virtual Tile* Clone() const = 0;
};

class TexturedTile : public Tile
{
public:
	TexturedTile()
		: m_SubTexId(Sprite::Sub::Void) {}
	TexturedTile(Sprite::Sub subTexId)
		: m_SubTexId(subTexId) {}

	virtual void OnUpdate(const glm::vec3& pos, Timestep ts) override
	{
		auto subTex = Sprite::GetSub(m_SubTexId);
		Renderer2D::DrawQuad(pos, subTex->GetSize(), subTex);
	}
	virtual void OnEvent(Event& e) override {}

	virtual Tile* Clone() const override;

private:
	Sprite::Sub m_SubTexId;
};

class PresetTile
{
public:
	static Tile* GrassTile;

	static void Init();
};
