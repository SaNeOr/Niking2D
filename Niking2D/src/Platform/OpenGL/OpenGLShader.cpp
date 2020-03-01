#include "n2pch.h"
#include "OpenGLShader.h"


#include "glad/glad.h"
#include <string> 

#include <glm/gtc/type_ptr.hpp>

namespace Niking2D {

	Niking2D::OpenGLShader::OpenGLShader(const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		// Read our shaders into the appropriate buffers
		std::string vertexSource = vertexSrc;// Get source code for vertex shader.
		std::string fragmentSource = fragmentSrc;// Get source code for fragment shader.

			// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar *source = (const GLchar *)vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			//N2_CORE_ERROR("Vertex shader compliation failure!");
			N2_CORE_ERROR("Vertex shader compliation failure! {0}", infoLog.data());
			N2_ASSERT(false, "Vertex shader compliation failure!");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar *)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			N2_CORE_ERROR("Fragment shader compliation failure! {0}", infoLog.data());
			N2_ASSERT(false, "Fragment shader compliation failure!");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		// Link our program
		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			N2_CORE_ERROR("Shader linked failure! {0}", infoLog.data());
			N2_ASSERT(false, "Shader linked failure!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string & name, const int values)
	{
		//int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(GetUniformLocation(name), values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string & name, const float values)
	{
		//int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(GetUniformLocation(name), values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string & name, const glm::vec2 & values)
	{
		//int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(GetUniformLocation(name), values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string & name, const glm::vec4& values)
	{
		//int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(GetUniformLocation(name), values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string & name, const glm::vec3 & values)
	{
		//int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(GetUniformLocation(name), values.x, values.y, values.z);
	}


	void OpenGLShader::UploadUniformMat3(const std::string & name, const glm::mat3 & matrix)
	{
		//int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		//int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}


	int OpenGLShader::GetUniformLocation(const std::string & name)
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		int location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1){

			N2_CORE_WARN("Warning: uniform '{0}' doesn't exist or use!", name);
		}
		m_UniformLocationCache[name] = location;
		return location;
	}


}
