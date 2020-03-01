#pragma once

#include "Niking2D/Renderer/Texture.h"

#include <string>
#include <glad/glad.h>


namespace Niking2D {

	class OpenGLTexture2D :public Texture2D {
	public:
		 
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual void Bind(unsigned int slot = 0) const override;
		virtual void Unbind() const override;


		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }


	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, channels;
	};
}