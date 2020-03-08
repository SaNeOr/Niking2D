#include "n2pch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace Niking2D {

	Ref<VertexArray> Niking2D::VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: {N2_CORE_ASSERT(false, "RendererAPI::None is currently is not supported!"); return nullptr; }
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLVertexArray>();
		}

		N2_CORE_ASSERT(false, "Unkonw RendererAPI!");
		return nullptr;
	}

}
