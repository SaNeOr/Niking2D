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
		N2_PROFILE_FUNCTION();

		std::string source = ReadFile(filepath);
		auto shaderSource = PreProcess(source);
		Compile(shaderSource);

		//	assets/shaders/texture.shader	==extract=> texture as m_Name;
		size_t lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		size_t lastDot = filepath.rfind(".");
		size_t count = lastDot == std::string::npos ? filepath.size() - lastSlash: lastDot - lastSlash;

		m_Name = filepath.substr(lastSlash, count);

	}
	Niking2D::OpenGLShader::OpenGLShader(const std::string& name, const std::string & vertexSrc, const std::string & fragmentSrc)
		:m_Name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;

		Compile(sources);

	}

	OpenGLShader::~OpenGLShader()
	{
		N2_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		N2_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		N2_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		N2_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& martix)
	{
		N2_PROFILE_FUNCTION();

		UploadUniformMat4(name, martix);
	}

	void OpenGLShader::SeFloat(const std::string& name, float value)
	{
		N2_PROFILE_FUNCTION();

		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SeFloat4(const std::string& name, const glm::vec4& values)
	{
		N2_PROFILE_FUNCTION();

		UploadUniformFloat4(name, values);
	}

	void OpenGLShader::UploadUniformInt(const std::string & name, const int values)
	{
		N2_PROFILE_FUNCTION();

		//int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(GetUniformLocation(name), values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string & name, const float values)
	{
		N2_PROFILE_FUNCTION();

		//int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(GetUniformLocation(name), values);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		N2_PROFILE_FUNCTION();

		//int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(GetUniformLocation(name), values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string & name, const glm::vec4& values)
	{
		N2_PROFILE_FUNCTION();

		//int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(GetUniformLocation(name), values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string & name, const glm::vec3 & values)
	{
		N2_PROFILE_FUNCTION();

		//int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(GetUniformLocation(name), values.x, values.y, values.z);
	}


	void OpenGLShader::UploadUniformMat3(const std::string & name, const glm::mat3 & matrix)
	{
		N2_PROFILE_FUNCTION();

		//int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		N2_PROFILE_FUNCTION();

		//int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}


	int OpenGLShader::GetUniformLocation(const std::string & name)
	{
		N2_PROFILE_FUNCTION();

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
		N2_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);

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
		N2_PROFILE_FUNCTION();

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
		N2_PROFILE_FUNCTION();

		// Read our shaders into the appropriate buffers
		//std::string vertexSource = shaderSources[GL_VERTEX_SHADER];// Get source code for vertex shader.
		//std::string fragmentSource = shaderSources[GL_FRAGMENT_SHADER];// Get source code for fragment shader.

		GLuint program = glCreateProgram();
		N2_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now!");
		std::array<GLuint, 2> glShaderIDs; 
		int glShaderIdIndex = 0;
		//glShaderIDs.reserve(shaderSources.size());


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
			glShaderIDs[glShaderIdIndex++] = shader;

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
