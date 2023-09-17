#pragma once

#include "gkpch.h"

#include "Gonk/Core/Core.h"
#include "Gonk/Events/Event.h"

namespace Gonk {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width, Height;

		WindowProps(const std::string& title = "Gonk Engine",
			uint32_t width = 1280,
			uint32_t height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class GONK_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual inline void* GetNativeWindow() const = 0;

		virtual void Shutdown() = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());

	};
}