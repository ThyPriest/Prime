
#include "pch.h"
#include "Camera2D.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Prime
{
	Camera2D::Camera2D(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::mat4(glm::ortho(left, right, bottom, top, -1.0f, 1.0f));
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera2D::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera2D::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		CalculateViewMatrix();
	}

	void Camera2D::CalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera2D::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		CalculateViewMatrix();
	}
}