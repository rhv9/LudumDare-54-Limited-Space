#pragma once
#include <Gonk.h>
#include "Entities/Player.h"
#include "Tile.h"

using namespace Gonk;

class Level
{
public:
	Level() = default;
	virtual ~Level() {}

	virtual void OnUpdate(Timestep ts) = 0;
	virtual void OnEvent(Event& e) = 0;

	virtual bool InMapBounds(int x, int y) const = 0;
};

class TestLevel : public Level
{
public:
	TestLevel();
	virtual ~TestLevel() override;

	virtual void OnUpdate(Timestep ts) override;
	virtual void OnEvent(Event& e) override;

	virtual bool InMapBounds(int x, int y) const override;
	
private:
	Player m_Player;

	Tile** m_Map;
	int m_Width, m_Height;

};