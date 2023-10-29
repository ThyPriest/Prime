#pragma once

namespace Prime
{
	class Layer
	{
	public:
		Layer() = default;
		virtual ~Layer() = default;

		virtual void Attach() {}
		virtual void Detach() {}

		virtual void Update() {}
		virtual void SubscribeToEvents() {}
	};
}
