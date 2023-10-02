#pragma once
#include <Gonk.h>

using namespace Gonk;

enum class CollisionType : int
{
	Box = 0,
	Circle,
};

struct CollisionShape
{
	virtual bool Collides(const CollisionShape& other) = 0;

	virtual CollisionType GetType() const = 0;
	virtual void Render(const glm::vec4& col) const = 0;
	virtual void Render() const { Render({ 1.0f, 1.0f, 1.0f, 1.0f }); }
};

struct CollisionBox : public CollisionShape
{
	CollisionBox(float x, float y, float width, float height);

	virtual bool Collides(const CollisionShape& other) override;
	virtual CollisionType GetType() const override { return CollisionType::Box; }

	virtual void Render(const glm::vec4& col) const override;

	float X, Y, W, H;
};

struct CollisionCircle : public CollisionShape
{
	CollisionCircle(float x, float y, float radius);

	virtual bool Collides(const CollisionShape& other) override;
	virtual CollisionType GetType() const override { return CollisionType::Circle; }

	virtual void Render(const glm::vec4& col) const override;

	float X, Y, Radius;
};