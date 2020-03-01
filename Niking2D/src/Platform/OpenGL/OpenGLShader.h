#pragma once
#include <unordered_map>
#include "Niking2D/Renderer/Shader.h"

namespace Niking2D {
	class OpenGLShader:public Shader {
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;



		void UploadUniformInt(const std::string& name, const int values);

		void UploadUniformFloat(const std::string& name, const float values);
		void UploadUniformFloat(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		int GetUniformLocation(const std::string& name);
	private:
		unsigned int m_RendererID;
		std::unordered_map<std::string, int> m_UniformLocationCache;

	};
}