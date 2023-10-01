#include "Level.h"
#include <Gonk.h>

using namespace Gonk;

ForestLevel::ForestLevel()
{
	player.SetPos({ -32.0f, 0.0f, 0.0f });
}

void ForestLevel::OnUpdate(Timestep ts)
{
	player.OnUpdate(ts);
}

void ForestLevel::OnEvent(Event& e)
{
	player.OnEvent(e);
}


