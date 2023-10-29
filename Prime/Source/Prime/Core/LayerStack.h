#pragma once

#include "Core.h"
#include "Layer.h"
#include <vector>

namespace Prime
{
	class PRIME_API LayerStack
	{
	public:
		static void Shutdown();

		static Layer* GetTopLayer();
		static bool IsEmpty();
		static void Update();

		static void PushLayer(Layer* layer);
		static void PushLayerTop(Layer* layer);
		static void PopLayer(Layer* layer);
		static void PopLayerTop(Layer* layer);


	private:
		struct LayerStackData
		{
			std::vector<Layer*> Layers;
			int LayerInsertIndex = 0;
		};

		static LayerStackData* s_Data;
	};
}