#include "n2pch.h"

#include "Renderer.h"


namespace Niking2D {

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArrary)
	{
		vertexArrary->Bind();

		RenderCommand::DrawIndexed(vertexArrary);
	}

}