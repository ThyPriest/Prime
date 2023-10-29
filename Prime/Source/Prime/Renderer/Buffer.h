#pragma once

#include "Prime/Core/Core.h"
#include <string>
#include <vector>

namespace Prime
{
	class BufferElement
	{
	public:
		std::string Name = "";
		ShaderDataType Type = ShaderDataType::Float3;
		uint32_t Size = 0;
		uint32_t Offset = 0;
		bool Normalized = false;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized)
		{
			Name = name;
			Type = type;
			Size = ShaderDataTypeSize(type);
			Normalized = normalized;
		}

		uint32_t GetComponentCount() const
		{
			return ShaderDataTypeCount(Type);
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferElement>& bufferElements)
		{
			m_BufferElements = bufferElements;
			CalcaulateOffsetAndStride();
		}

		inline const std::vector<BufferElement>& GetBufferElemets() const { return m_BufferElements; }
		inline const uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_BufferElements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_BufferElements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_BufferElements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_BufferElements.end(); }

	private:
		void CalcaulateOffsetAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& bufferElement : m_BufferElements)
			{
				bufferElement.Offset = offset;
				offset += bufferElement.Size;
				m_Stride += bufferElement.Size;
			}
		}

	private:
		std::vector<BufferElement> m_BufferElements;
		uint32_t m_Stride = 0;
	};

	class PRIME_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
		static Ref<VertexBuffer> Create(uint32_t size);
	};

	class PRIME_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};
}