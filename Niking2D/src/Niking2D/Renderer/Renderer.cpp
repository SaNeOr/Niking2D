#include "n2pch.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "Niking2D/Renderer/Renderer2D.h"
namespace Niking2D {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		N2_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		N2_PROFILE_FUNCTION();

		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
		N2_PROFILE_FUNCTION();

	}

	void Renderer::Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexArrary, const glm::mat4& transform)
	{
		N2_PROFILE_FUNCTION();

		shader->Bind();
		vertexArrary->Bind();
		
		
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", Renderer::m_SceneData->ViewProjectionMatrix);

		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);


		RenderCommand::DrawIndexed(vertexArrary);
	}

}