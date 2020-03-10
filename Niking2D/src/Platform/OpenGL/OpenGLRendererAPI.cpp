#include "n2pch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

void Niking2D::OpenGLRendererAPI::Init()
{
	N2_PROFILE_FUNCTION();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
}

void Niking2D::OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
	N2_PROFILE_FUNCTION();

	glClearColor(color.r, color.g, color.b, color.a);
}

void Niking2D::OpenGLRendererAPI::Clear()
{
	N2_PROFILE_FUNCTION();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Niking2D::OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
{
	N2_PROFILE_FUNCTION();

	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}
