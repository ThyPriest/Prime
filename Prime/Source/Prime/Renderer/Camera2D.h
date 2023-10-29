#pragma once

#include "Prime/Core/Core.h"
#include "glm/glm.hpp"

namespace Prime
{
	class PRIME_API Camera2D
	{
	public:
		Camera2D() = default;
		Camera2D(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position);

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation);

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void CalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.0f);

		glm::vec3 m_Position = glm::vec3(0.0f);
		float m_Rotation = 0.0f;
	};
}