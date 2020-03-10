#pragma once
#include <unordered_map>
#include "Niking2D/Renderer/Shader.h"
#include <glm/glm.hpp>

typedef unsigned int GLenum;
namespace Niking2D {
	class OpenGLShader:public Shader {
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const override { return m_Name; }


		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& martix) override;
		virtual void SeFloat(const std::string& name, float value) override;
		virtual void SeFloat4(const std::string& name, const glm::vec4& values) override;

		void UploadUniformInt(const std::string& name, const int values);

		void UploadUniformFloat(const std::string& name, const float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		int GetUniformLocation(const std::string& name);

		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string> shaderSources);
	private:

		unsigned int m_RendererID;
		std::string m_Name;
		std::unordered_map<std::string, int> m_UniformLocationCache;

	};
}