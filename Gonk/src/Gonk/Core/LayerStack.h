#pragma once

#include "Gonk/Core/Layer.h"

// TODO:: Why include vector when you can include precompiled headers or in cpp
#include <vector>

namespace Gonk {

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		int m_LayerInsertIndex = 0;

	};

}

