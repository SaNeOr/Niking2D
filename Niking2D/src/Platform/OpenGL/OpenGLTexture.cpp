#include "n2pch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

namespace Niking2D {



	OpenGLTexture2D::OpenGLTexture2D(const std::string & path)
		:m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), channels(0)
	{
		N2_PROFILE_FUNCTION();

		stbi_set_flip_vertically_on_load(1);
		m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &channels, 0);
		N2_CORE_ASSERT(m_LocalBuffer, "Failed to load image");

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		N2_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		//glGenTextures(1, &m_RendererID);
		//glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);	//	GL_CLAMP_TO_EDGE
		
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, m_LocalBuffer);		//	GL_RGBA: source format

		glBindTexture(GL_TEXTURE_2D, 0);

		if (m_LocalBuffer)
			stbi_image_free(m_LocalBuffer);

	}

	OpenGLTexture2D::OpenGLTexture2D(unsigned int width, unsigned int height)
		:m_Width(width), m_Height(height)
	{
		N2_PROFILE_FUNCTION();

		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}


	OpenGLTexture2D::~OpenGLTexture2D()
	{
		N2_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(unsigned int slot) const
	{
		N2_PROFILE_FUNCTION();

		//glActiveTexture(GL_TEXTURE0 + slot);
		//glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glBindTextureUnit(slot, m_RendererID);
	}

	void OpenGLTexture2D::Unbind() const
	{
		N2_PROFILE_FUNCTION();

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture2D::SetData(void* data, unsigned int size)
	{
		N2_PROFILE_FUNCTION();

		unsigned int bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		N2_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

}
