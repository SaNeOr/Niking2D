#pragma once

#include <string>
#include <glm/glm.hpp>


namespace Niking2D {
	class Shader {
	public:
		//Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& filepath);
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}