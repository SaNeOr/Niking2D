#pragma once

#include "RenderCommand.h"

namespace Niking2D {

	class Renderer {

	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArrary);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI();}

	};

}