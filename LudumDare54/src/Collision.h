#pragma once
#include <Gonk.h>

using namespace Gonk;

class CollisionShape
{
public:
	virtual bool Collides(const CollisionShape& other) = 0;
};

class CollisionBox : public CollisionShape
{
public:
	CollisionBox(int x, int y, int width, int height);

	virtual bool Collides(const CollisionShape& other) override;

	int m_X, m_Y, m_Width, m_Height;
};