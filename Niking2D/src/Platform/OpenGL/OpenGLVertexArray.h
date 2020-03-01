#pragma once

#include "Niking2D/Renderer/VertexArray.h"
#include <vector>

namespace Niking2D {
	class OpenGLVertexArray :public VertexArray {
	public:
		OpenGLVertexArray();

		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind()const override;

		virtual void AddVertexBuffer(const Ref< VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref< IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer> >& GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer> & GetIndexBuffers() const override { return m_IndexBuffer; }

	private:
		unsigned int m_RendererID;
		std::vector<Ref<VertexBuffer> > m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;

	};

}