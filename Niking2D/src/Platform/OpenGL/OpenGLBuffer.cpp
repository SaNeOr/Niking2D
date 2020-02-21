#include "n2pch.h"
#include "OpenGLBuffer.h"
#include "glad/glad.h"

namespace Niking2D {


	/////////////////////////////////////////////////////////////////////////////////
	//  VertexBuffer  ///////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	Niking2D::OpenGLVertexBuffer::OpenGLVertexBuffer(float * vertices, unsigned int size)
	{
		glCreateBuffers(1, &m_RendererID);
		//glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/////////////////////////////////////////////////////////////////////////////////
	//  IndexBuffer  ////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int * indices, unsigned int count)
		:m_Count(count)
	{
		//glGenBuffers(1, &m_RendererID);
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
 	}

}
