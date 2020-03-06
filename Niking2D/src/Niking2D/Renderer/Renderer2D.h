#pragma once

#include "Niking2D/Renderer/OrthographicCamera.h"
#include "Niking2D/Renderer/Texture.h"

namespace Niking2D {

	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();
							         
		static void BeginScene(const OrthograhicCamera& camera);
		static void EndScene();

		//	Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
	};

}