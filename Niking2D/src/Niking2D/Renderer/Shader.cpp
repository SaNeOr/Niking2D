#include "n2pch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace Niking2D {

	Shader * Shader::Create(const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: {N2_CORE_ASSERT(false, "RendererAPI::None is currently is not supported!"); return nullptr; }
			case RendererAPI::API::OpenGL:		return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		N2_CORE_ASSERT(false, "Unkonw RendererAPI!");
		return nullptr;
	}


}
