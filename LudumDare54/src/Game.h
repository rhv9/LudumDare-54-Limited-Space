#pragma once

#include <Gonk.h>
#include "Level/Level.h"

using namespace Gonk;

class Game : public Layer
{
public:
	static Timestep s_TimePassed;
	static OrthographicCameraController s_CameraController;
	static std::vector<std::string> s_ImGuiPrint;

	static int WIDTH, HEIGHT;
	
public:
	template<typename... Args>
	static void ImGuiPrint(const std::format_string<Args...> fmt, Args&&... args);

public:
	Game();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Timestep ts) override;
	virtual void OnEvent(Event& event) override;

	virtual void OnImGuiRender() override;

private:
	Level* m_Level;

};

template<typename... Args>
inline void Game::ImGuiPrint(const std::format_string<Args...> fmt, Args&&... args)
{
	Game::s_ImGuiPrint.push_back(std::vformat(fmt.get(), std::make_format_args(args...)));
}


class GameApplication : public Application
{
public:
	GameApplication();
	~GameApplication();

private:
	Game* m_GameLayer;
};
