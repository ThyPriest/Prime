
#include "pch.h"
#include "LayerStack.h"

namespace Prime
{
	LayerStack::LayerStackData* LayerStack::s_Data = new LayerStack::LayerStackData();

	void LayerStack::Shutdown()
	{
		for (Layer* layer : s_Data->Layers)
		{
			layer->Detach();
			delete layer;
		}
		delete s_Data;
		s_Data = nullptr;
	}

	Layer* LayerStack::GetTopLayer()
	{
		for (auto it = s_Data->Layers.end(); it != s_Data->Layers.begin(); )
		{
			return (*--it);
		}
		return nullptr;
	}

	bool LayerStack::IsEmpty()
	{
		if (s_Data->LayerInsertIndex == 0) { return true; }
		else if (s_Data->LayerInsertIndex > 0) { return false; }
	}

	void LayerStack::Update()
	{
		for (Layer* layer : s_Data->Layers)
		{
			layer->Update();
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		s_Data->Layers.emplace(s_Data->Layers.begin() + s_Data->LayerInsertIndex, layer);
		s_Data->LayerInsertIndex++;
		layer->Attach();
	}

	void LayerStack::PushLayerTop(Layer* layer)
	{
		s_Data->Layers.emplace_back(layer);
		layer->Attach();

	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(s_Data->Layers.begin(), s_Data->Layers.begin() + s_Data->LayerInsertIndex, layer);
		if (it != s_Data->Layers.begin() + s_Data->LayerInsertIndex)
		{
			layer->Detach();
			s_Data->Layers.erase(it);
			s_Data->LayerInsertIndex--;
		}
	}

	void LayerStack::PopLayerTop(Layer* layer)
	{
		auto it = std::find(s_Data->Layers.begin() + s_Data->LayerInsertIndex, s_Data->Layers.end(), layer);
		if (it != s_Data->Layers.end())
		{
			layer->Detach();
			s_Data->Layers.erase(it);
		}
	}
}
