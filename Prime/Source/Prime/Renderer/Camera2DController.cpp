
#include "pch.h"
#include "Camera2DController.h"
#include "Prime/Input/Input.h"

namespace Prime
{
	Camera2DController::Camera2DController(float aspectRatio, bool rotation)
	{
		m_AspectRatio = aspectRatio;
		m_Camera = Camera2D(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
			-m_ZoomLevel, m_ZoomLevel);

		m_EnableRotation = rotation;
	}

	void Camera2DController::Update()
	{
		if (Input::IsKeyPressed(Key::A))
		{
			m_Position.x -= cos(glm::radians(m_Rotation)) *
				m_TranslationSpeed * GameTime::GetDeltaTime();

			m_Position.y -= sin(glm::radians(m_Rotation)) *
				m_TranslationSpeed * GameTime::GetDeltaTime();
		}
		else if (Input::IsKeyPressed(Key::D))
		{
			m_Position.x += cos(glm::radians(m_Rotation)) *
				m_TranslationSpeed * GameTime::GetDeltaTime();

			m_Position.y += sin(glm::radians(m_Rotation)) *
				m_TranslationSpeed * GameTime::GetDeltaTime();
		}

		if (Input::IsKeyPressed(Key::W))
		{
			m_Position.x += -sin(glm::radians(m_Rotation)) *
				m_TranslationSpeed * GameTime::GetDeltaTime();
			m_Position.y += cos(glm::radians(m_Rotation)) *
				m_TranslationSpeed * GameTime::GetDeltaTime();
		}
		else if (Input::IsKeyPressed(Key::S))
		{
			m_Position.x -= -sin(glm::radians(m_Rotation)) *
				m_TranslationSpeed * GameTime::GetDeltaTime();

			m_Position.y -= cos(glm::radians(m_Rotation)) *
				m_TranslationSpeed * GameTime::GetDeltaTime();
		}

		if (m_EnableRotation)
		{
			if (Input::IsKeyPressed(Key::Q))
				m_Rotation += m_RotationSpeed * GameTime::GetDeltaTime();;
			if (Input::IsKeyPressed(Key::E))
				m_Rotation -= m_RotationSpeed * GameTime::GetDeltaTime();;

			if (m_Rotation > 180.0f)
				m_Rotation -= 360.0f;
			else if (m_Rotation <= -180.0f)
				m_Rotation += 360.0f;

			m_Camera.SetRotation(m_Rotation);
		}

		m_Camera.SetPosition(m_Position);
	}

	void Camera2DController::SubscribeToEvents()
	{
		Dispatcher::SubscribeToEvent<KeyPressedEvent>(this,
			&Camera2DController::OnKeyPressed);

		Dispatcher::SubscribeToEvent<MouseScrolledEvent>(this,
			&Camera2DController::OnMouseScrolled);

		Dispatcher::SubscribeToEvent<WindowResizeEvent>(this,
			&Camera2DController::OnWindowResize);
	}

	void Camera2DController::OnKeyPressed(const Event& event)
	{
		auto e = Dispatcher::CastToEvent<KeyPressedEvent>(event);

		if (e.GetKeyMods() == Mod::CONTROL)
		{
			if (e.GetKeyCode() == Key::Equal)
			{
				m_ZoomLevel -= .3f;
				m_ZoomLevel = std::max(m_ZoomLevel, 0.3f);
			}
			else if (e.GetKeyCode() == Key::Minus)
			{
				m_ZoomLevel += .3f;
				m_ZoomLevel = std::min(m_ZoomLevel, 2.5f);
			}
		}

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
			-m_ZoomLevel, m_ZoomLevel);
	}

	void Camera2DController::OnMouseScrolled(const Event& event)
	{
		auto e = Dispatcher::CastToEvent<MouseScrolledEvent>(event);

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
			-m_ZoomLevel, m_ZoomLevel);
	}

	void Camera2DController::OnWindowResize(const Event& event)
	{
		auto e = Dispatcher::CastToEvent<WindowResizeEvent>(event);

		m_AspectRatio = ((float)e.GetWidth() / (float)e.GetHeight());
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
			-m_ZoomLevel, m_ZoomLevel);
	}
}