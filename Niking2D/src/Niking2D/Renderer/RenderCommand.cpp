#include "n2pch.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Niking2D {

	RendererAPI* RenderCommand::s_RendererAPI =  RendererAPI::GetAPI() == RendererAPI::API::OpenGL?  new OpenGLRendererAPI(): nullptr;

}