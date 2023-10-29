#pragma once

#include "Prime/Prime.h"

namespace Prime
{
	class TerraLayer : public Layer
	{
	public:
		TerraLayer() = default;
		~TerraLayer() = default;

		void Attach() override;
		void Detach() override;

		void Update() override;
		void SubscribeToEvents() override;

	private:
		//Camera2DController m_Camera2DController;
	};
}