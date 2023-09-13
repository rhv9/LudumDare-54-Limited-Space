#pragma once

#include "Gonk/Core/Window.h"

#include <GLFW/glfw3.h>
#include "Gonk/Renderer/GraphicsContext.h"

namespace Gonk {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.m_Width; }
		inline unsigned int GetHeight() const override { return m_Data.m_Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		virtual inline void* GetNativeWindow() const override { return (void*)m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown() override;
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData {
			std::string Title;
			unsigned int m_Width, m_Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};
		WindowData m_Data;

		bool m_Shutdown = false;


	};

}