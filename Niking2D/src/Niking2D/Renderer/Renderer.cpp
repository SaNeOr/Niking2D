#include "n2pch.h"

#include "Renderer.h"


namespace Niking2D {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthograhicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader,const std::shared_ptr<VertexArray>& vertexArrary, const glm::mat4& transform)
	{
		shader->Bind();
		vertexArrary->Bind();
		shader->UploadUniformMat4("u_ViewProjection", Renderer::m_SceneData->ViewProjectionMatrix);

		shader->UploadUniformMat4("u_Transform", transform);

		RenderCommand::DrawIndexed(vertexArrary);
	}

}