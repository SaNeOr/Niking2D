#include "n2pch.h"
#include "Texture.h"
#include "Renderer.h"


#include "Platform/OpenGL/OpenGLTexture.h"

namespace Niking2D {

	Ref<Texture2D> Texture2D::Create(const std::string & path)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:		{N2_CORE_ASSERT(false, "RendererAPI::None is currently is not supported!"); return nullptr; }
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(path);
		}

		N2_CORE_ASSERT(false, "Unkonw RendererAPI!");
		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(unsigned int width, unsigned int height)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:		{N2_CORE_ASSERT(false, "RendererAPI::None is currently is not supported!"); return nullptr; }
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(width, height);
		}

		N2_CORE_ASSERT(false, "Unkonw RendererAPI!");
		return nullptr;
	}
}