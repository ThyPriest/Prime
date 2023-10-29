
#include "pch.h"
#include "OpenGLShader.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace Prime
{
	OpenGLShader::OpenGLShader(const std::string& vertSource, const std::string& fragSource, bool read)
	{
		std::string vertShaderSource = "";
		std::string fragShaderSource = "";

		if (read)
		{
			vertShaderSource = ReadFile(vertSource);
			fragShaderSource = ReadFile(fragSource);
		}

		m_VertexShader = Compile(vertShaderSource, GL_VERTEX_SHADER);
		m_FragmentShader = Compile(fragShaderSource, GL_FRAGMENT_SHADER);

		CreateProgram();
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteShader(m_VertexShader);
		glDeleteShader(m_FragmentShader);
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		auto it = m_UniformLocations.find(name);
		if (it == m_UniformLocations.end())
		{
			m_UniformLocations[name] = glGetUniformLocation(m_RendererID, name.c_str());
		}

		return m_UniformLocations[name];
	}

	std::string OpenGLShader::ReadFile(const std::string& shaderSource)
	{
		std::string result;
		std::ifstream myFile(shaderSource, std::ios::in | std::ios::binary);
		if (myFile)
		{
			myFile.seekg(0, std::ios::end);
			size_t size = myFile.tellg();
			if (size != -1)
			{
				result.resize(size);
				myFile.seekg(0, std::ios::beg);
				myFile.read(&result[0], size);
			}
			else
			{
				PRIME_ERROR("Could not read from file {0}", shaderSource);
			}
		}
		else
		{
			PRIME_ERROR("Could not read from file {0}", shaderSource);
		}

		return result;
	}

	void OpenGLShader::CreateProgram()
	{
		m_RendererID = glCreateProgram();

		glAttachShader(m_RendererID, m_VertexShader);
		glAttachShader(m_RendererID, m_FragmentShader);
		glLinkProgram(m_RendererID);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_RendererID);
			glDeleteShader(m_VertexShader);
			glDeleteShader(m_FragmentShader);

			PRIME_ERROR("{0}", infoLog.data());
			PRIME_ASSERT(false, "Program linkage failed");
		}

		glDetachShader(m_RendererID, m_VertexShader);
		glDetachShader(m_RendererID, m_FragmentShader);
	}

	uint32_t OpenGLShader::Compile(std::string& source, GLenum type)
	{
		GLuint shader = glCreateShader(type);
		const GLchar* shaderSource = source.c_str();
		glShaderSource(shader, 1, &shaderSource, 0);
		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		{
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);
				PRIME_ERROR("{0}", infoLog.data());
				PRIME_ASSERT(false, "shader compilation failed");
			}

			return shader;
		}
	}
}