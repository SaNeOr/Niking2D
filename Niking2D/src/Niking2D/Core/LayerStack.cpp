#include "n2pch.h"
#include "LayerStack.h"


namespace Niking2D {

	Niking2D::LayerStack::LayerStack()
	{

	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers) {
			delete(layer);
		}
	}

	void LayerStack::PushLayer(Layer * layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverLayer(Layer * overlayer)
	{
		m_Layers.emplace_back(overlayer);
	}

	void LayerStack::PopLayer(Layer * layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverLayer(Layer * overlayer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlayer);
		if (it != m_Layers.end())
			m_Layers.erase(it);

	}

	

}
