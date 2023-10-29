#pragma once

#include "Prime/Core/Core.h"
#include "Camera2D.h"
#include "Prime/Core/GameTime.h"
#include "Prime/Event/EventSystem.h"

namespace Prime
{
	class PRIME_API Camera2DController
	{
	public:
		Camera2DController() = default;
		Camera2DController(float aspectRatio, bool rotation = false);

		void Update();

		Camera2D& GetCamera() { return m_Camera; }
		const Camera2D& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

		void SubscribeToEvents();

	private:
		void OnKeyPressed(const Event& event);
		void OnMouseScrolled(const Event& event);
		void OnWindowResize(const Event& event);

	private:
		float m_AspectRatio = 1.7776f;
		float m_ZoomLevel = 1.0f;
		Camera2D m_Camera;

		bool m_EnableRotation = false;

		glm::vec3 m_Position = glm::vec3(0.0f);
		float m_Rotation = 0.0f;
		float m_TranslationSpeed = 5.0f, m_RotationSpeed = 180.0f;
	};

}