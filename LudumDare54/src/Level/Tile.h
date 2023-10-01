#pragma once

#include <Gonk.h>

using namespace Gonk;

class Tile {

	Tile();

	virtual void Update(Timestep ts);
	virtual void OnEvent(Event& e);

};