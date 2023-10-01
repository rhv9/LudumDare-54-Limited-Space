#pragma once
#include <Gonk.h>
#include "Entities/Player.h"

using namespace Gonk;

class Level
{
public:
	Level() = default;

	virtual void OnUpdate(Timestep ts) = 0;
	virtual void OnEvent(Event& e) = 0;
};


class ForestLevel : public Level
{
public:
	ForestLevel();

	virtual void OnUpdate(Timestep ts) override;
	virtual void OnEvent(Event& e) override;

private:
	Player player;

};