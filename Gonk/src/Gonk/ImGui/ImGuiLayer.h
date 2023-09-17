#pragma once

#include "Gonk/Core/Layer.h"

#include "Gonk/Events/ApplicationEvent.h"
#include "Gonk/Events/MouseEvent.h"
#include "Gonk/Events/KeyEvent.h"

namespace Gonk {

	class GONK_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& event) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block ; }

	private:
		float m_Time = 0.0f;

		bool m_BlockEvents = true;
	};

}