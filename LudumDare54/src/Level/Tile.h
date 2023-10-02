#pragma once
#include <Gonk.h>
#include "Sprite.h"

using namespace Gonk;

class Tile 
{
public:
	// TODO: bad
	static const int SIZE = 16;

public:
	Tile() = default;
		
	virtual void OnUpdate(const glm::vec3& pos, Timestep ts) = 0;
	virtual void OnEvent(Event& e) {}

	virtual bool Collidable() const = 0;

	virtual Tile* Clone() const { GK_WARN("Base tile clone is being used!"); return nullptr; }
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
		Renderer2D::DrawQuad(pos, Sprite::SIZE, subTex);
	}

	virtual bool Collidable() const override { return false; }

	virtual Tile* Clone() const override;

private:
	Sprite::Sub m_SubTexId;
};

class AnimatedTile : public Tile
{
public:
	AnimatedTile()
		: m_Gif(Sprite::Gif::Void), m_AnimationSpeed(1) {}
	AnimatedTile(Sprite::Gif gif, float animationSpeed)
		: m_Gif(gif), m_AnimationSpeed(animationSpeed) {}

	virtual void OnUpdate(const glm::vec3& pos, Timestep ts) override;

	virtual bool Collidable() const override { return false; }

private:
	Sprite::Gif m_Gif;
	float m_AnimationSpeed;
};

class PresetTile
{
public:
	static Tile* GrassTile;
	static Tile* WaterTile;

	static void Init();
};
