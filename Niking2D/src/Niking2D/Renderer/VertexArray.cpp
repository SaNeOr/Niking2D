#include "n2pch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace Niking2D {

	VertexArray* Niking2D::VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {

		case RendererAPI::None: {N2_CORE_ASSERT(false, "RendererAPI::None is currently is not supported!"); return nullptr; }
		case RendererAPI::OpenGL:		return new OpenGLVertexArray();
		}

		N2_CORE_ASSERT(false, "Unkonw RendererAPI!");
		return nullptr;
	}

}
