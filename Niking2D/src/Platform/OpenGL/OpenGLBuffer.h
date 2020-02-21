#pragma once

#include "Niking2D/Renderer/Buffer.h"

namespace Niking2D {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:

		OpenGLVertexBuffer(float* vertices, unsigned int size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

	private:
		unsigned int m_RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:

		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual unsigned int GetCount() const override {return m_Count;}
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};

}