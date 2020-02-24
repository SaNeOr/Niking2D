#include "n2pch.h"
#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"


namespace Niking2D {

	VertexBuffer * Niking2D::VertexBuffer::Create(float * vertices, unsigned int size)
	{
		switch (Renderer::GetAPI()){
		
			case RendererAPI::API::None:			{N2_CORE_ASSERT(false, "RendererAPI::None is currently is not supported!"); return nullptr; }
			case RendererAPI::API::OpenGL:		return new OpenGLVertexBuffer(vertices, size);
		}

		N2_CORE_ASSERT(false, "Unkonw RendererAPI!");
		return nullptr;

	}

	IndexBuffer * Niking2D::IndexBuffer::Create(unsigned int* indices, unsigned int size)
	{
		switch (Renderer::GetAPI()) {

		case RendererAPI::API::None:			{N2_CORE_ASSERT(false, "RendererAPI::None is currently is not supported!"); return nullptr; }
		case RendererAPI::API::OpenGL:		return new OpenGLIndexBuffer(indices, size);
		}

		N2_CORE_ASSERT(false, "Unkonw RendererAPI!");
		return nullptr;

	}
}
