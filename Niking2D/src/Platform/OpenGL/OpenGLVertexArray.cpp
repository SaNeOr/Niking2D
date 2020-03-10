#include "n2pch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>
namespace Niking2D {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
			case Niking2D::ShaderDataType::Float:		return GL_FLOAT;
			case Niking2D::ShaderDataType::Float2:		return GL_FLOAT;
			case Niking2D::ShaderDataType::Float3:		return GL_FLOAT;
			case Niking2D::ShaderDataType::Float4:		return GL_FLOAT;
			case Niking2D::ShaderDataType::Mat3:		return GL_FLOAT;
			case Niking2D::ShaderDataType::Mat4:		return GL_FLOAT;
			case Niking2D::ShaderDataType::Int:			return GL_INT;
			case Niking2D::ShaderDataType::Int2:		return GL_INT;
			case Niking2D::ShaderDataType::Int3:		return GL_INT;
			case Niking2D::ShaderDataType::Int4:		return GL_INT;
			case Niking2D::ShaderDataType::Bool:		return GL_BOOL;
		}
		N2_CORE_ASSERT(false, "Unkonwn ShaderDataType!");
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		N2_PROFILE_FUNCTION();

		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		N2_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void Niking2D::OpenGLVertexArray::Bind() const
	{
		N2_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void Niking2D::OpenGLVertexArray::Unbind() const
	{
		N2_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void Niking2D::OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		N2_PROFILE_FUNCTION();

		N2_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		unsigned int index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponementCount(), ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		
		m_VertexBuffers.push_back(vertexBuffer);
	
	}

	void Niking2D::OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		N2_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}


}
