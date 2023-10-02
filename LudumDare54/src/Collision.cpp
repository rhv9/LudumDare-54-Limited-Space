#include "Collision.h"

#include "Sprite.h"

static bool sCollides(const CollisionBox& box, const CollisionCircle& circle)
{
	return false;
}

static bool sCollides(const CollisionBox& rect1, const CollisionBox& rect2)
{
	return (
		rect1.X < rect2.X + rect2.W &&
		rect1.X + rect1.W > rect2.X &&
		rect1.Y < rect2.Y + rect2.H &&
		rect1.Y + rect1.H > rect2.Y );
}

static bool sCollides(const CollisionCircle& circle1, const CollisionCircle& circle2)
{

	auto distance = glm::length(glm::vec2{ circle1.X, circle1.Y } - glm::vec2{circle2.X, circle2.Y});
	return distance <= circle1.Radius + circle2.Radius;
}

// BOX


CollisionBox::CollisionBox(float x, float y, float width, float height)
	: X(x), Y(y), W(width), H(height) {}


bool CollisionBox::Collides(const CollisionShape& other)
{
	if (other.GetType() == CollisionType::Box)
		return sCollides(*this, (CollisionBox&)other);

	else if (other.GetType() == CollisionType::Circle)
		return sCollides(*this, (CollisionCircle&)other);

	return false;
}

void CollisionBox::Render(const glm::vec4& col) const
{
	auto sprite = Sprite::GetSub(Sprite::Sub::CollisionBox);
	Renderer2D::DrawQuad({ X, Y, 0.9f }, {W, H}, sprite, 1.0f, col);
}


// CIRCLE


CollisionCircle::CollisionCircle(float x, float y, float radius)
	: X(x), Y(y), Radius(radius) {}

bool CollisionCircle::Collides(const CollisionShape& other)
{
	if (other.GetType() == CollisionType::Box)
		return sCollides((CollisionBox&)other , *this);

	else if (other.GetType() == CollisionType::Circle)
		return sCollides(*this, (CollisionCircle&)other);

	return false;
}

void CollisionCircle::Render(const glm::vec4& col) const
{
	auto sprite = Sprite::GetSub(Sprite::Sub::CollisionCircle);
	Renderer2D::DrawQuad({ X, Y, 0.9f }, { Radius*2.0f, Radius*2.0f }, sprite, 1.0f, col);
}
