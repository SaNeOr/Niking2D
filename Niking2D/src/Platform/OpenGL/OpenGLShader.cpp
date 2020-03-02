#include "n2pch.h"
#include "OpenGLShader.h"


#include "glad/glad.h"
#include <string> 

#include <fstream>

#include <glm/gtc/type_ptr.hpp>

namespace Niking2D {

	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex")							return GL_VERTEX_SHADER; 
		if (type == "fragment" || type == "pixel")		return GL_FRAGMENT_SHADER;

		N2_CORE_ASSERT(false, "Unkonw shader type '{0}'", type);
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string & filepath)
	{
		std::string source = ReadFile(filepath);
		auto shaderSource = PreProcess(source);
		Compile(shaderSource);

	}
	Niking2D::OpenGLShader::OpenGLShader(const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;

		Compile(sources);

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

	std::string OpenGLShader::ReadFile(const std::string & filepath)
	{

		std::string result;
		std::ifstream in(filepath, std::ios::in, std::ios::binary);

		if (in) {
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();

		}
		else {
			N2_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;

	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string & source)
	{
		std::unordered_map<GLenum, std::string> shaderSource;
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);

		//while (pos != std::string::npos) {
		//	size_t eol = source.find_first_of("\r\n", pos);
		//	N2_CORE_ASSERT(!(eol == std::string::npos), "Syntax error");
		//	size_t begin = pos + typeTokenLength + 1;
		//	std::string type = source.substr(begin, eol - begin);
		//}

		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
				N2_CORE_ASSERT(!(eol == std::string::npos), "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
				N2_CORE_ASSERT(ShaderTypeFromString(type), "Invaild shader type specified");
			
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSource[ShaderTypeFromString(type)] =
				source.substr(nextLinePos,
					pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));

		}




		return shaderSource;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string> shaderSources)
	{
		// Read our shaders into the appropriate buffers
		//std::string vertexSource = shaderSources[GL_VERTEX_SHADER];// Get source code for vertex shader.
		//std::string fragmentSource = shaderSources[GL_FRAGMENT_SHADER];// Get source code for fragment shader.

		GLuint program = glCreateProgram();
		std::vector<GLuint> glShaderIDs(shaderSources.size());

		for (auto& kv : shaderSources) {
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);
			const GLchar* sourceCstr = source.c_str();
			glShaderSource(shader, 1, &sourceCstr, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				// Use the infoLog as you see fit.

				// In this simple program, we'll just leave
				//N2_CORE_ERROR("Vertex shader compliation failure!");
				N2_CORE_ERROR("Vertex shader compliation failure! {0}", infoLog.data());
				N2_ASSERT(false, "Shader compliation failure!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs.push_back(shader);

		}

		m_RendererID = program;
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
			for (auto id : glShaderIDs) {
				glDeleteShader(id);
			}

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			N2_CORE_ERROR("Shader linked failure! {0}", infoLog.data());
			N2_ASSERT(false, "Shader linked failure!");
			return;
		}

		// Always detach shaders after a successful link.

		for (auto id : glShaderIDs) {
			glDetachShader(m_RendererID, id);
		}


	}




}
