#pragma once

#include <Gonk.h>
#include "Level/Level.h"

using namespace Gonk;

class GameLayer : public Layer
{
public:
	GameLayer();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Timestep ts) override;
	virtual void OnEvent(Event& event) override;

	virtual void OnImGuiRender() override;

private:
	int width = 1280, height = 720;
	Level* m_Level;

	OrthographicCameraController m_CameraController;
};

class Game : public Application
{
public:
	Game();
	~Game();

	static Timestep TimePassed;

	static const int SPRITE_SIZE = 16;
	static Ref<Texture2D> SpriteSheet;
};
