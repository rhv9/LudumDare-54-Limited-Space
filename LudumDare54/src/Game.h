#pragma once

#include <Gonk.h>
#include "Level/Level.h"

using namespace Gonk;

class Game : public Layer
{
public:
	Game();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Timestep ts) override;
	virtual void OnEvent(Event& event) override;

	virtual void OnImGuiRender() override;

public:
	static Timestep s_TimePassed;
	static OrthographicCameraController s_CameraController;

	static const int WIDTH = 1280, HEIGHT = 720;
private:
	Level* m_Level;



};

class GameApplication : public Application
{
public:
	GameApplication();
	~GameApplication();

private:
	Game* m_GameLayer;
};
