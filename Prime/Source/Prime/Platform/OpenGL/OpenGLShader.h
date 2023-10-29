#pragma once

#include "Prime/Core/Core.h"
#include "Prime/Renderer/Shader.h"

typedef unsigned int GLenum;

namespace Prime
{
	class PRIME_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertSource, const std::string& fragSource, bool read);
		~OpenGLShader() override;

		void Bind() const override;
		void UnBind() const override;

		void SetInt(const std::string& name, int value) override;
		void SetFloat(const std::string& name, float value) override;
		void SetFloat2(const std::string& name, const glm::vec2& value) override;
		void SetFloat3(const std::string& name, const glm::vec3& value) override;
		void SetFloat4(const std::string& name, const glm::vec4& value) override;
		void SetMat4(const std::string& name, const glm::mat4& value) override;
		void SetIntArray(const std::string& name, int* value, uint32_t count) override;

	private:
		int GetUniformLocation(const std::string& name);
		std::string ReadFile(const std::string& shaderSource);
		void CreateProgram();
		uint32_t Compile(std::string& source, GLenum type);

	private:
		RendererID m_RendererID = 0;
		uint32_t m_VertexShader = 0;
		uint32_t m_FragmentShader = 0;
		std::unordered_map<std::string, int> m_UniformLocations;

	};
}