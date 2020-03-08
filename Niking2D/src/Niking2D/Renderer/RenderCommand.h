#pragma once

#include "RendererAPI.h"
namespace Niking2D {

	class RenderCommand {

	public:
		inline static void Init() {

			s_RendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& color) {
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear() {
			s_RendererAPI->Clear();
		}


		inline static void DrawIndexed(const Ref<VertexArray>& vertexArrary) {
			s_RendererAPI->DrawIndexed(vertexArrary);
		}

	private:

		static RendererAPI* s_RendererAPI;
		 
	};

}