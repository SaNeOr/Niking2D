#pragma once
 
#include "Niking2D/Renderer/RendererAPI.h"


namespace Niking2D {

	class OpenGLRendererAPI : public RendererAPI {

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

	};
}