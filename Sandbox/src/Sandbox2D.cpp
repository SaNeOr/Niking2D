#include "Sandbox2D.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include <chrono>



Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
	
}

void Sandbox2D::OnAttach()
{

	//	======= Square
	m_SquareVA = Niking2D::VertexArray::Create();
	float squareVertices[4 * 5] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f, 0.5f,  0.0f,
		-0.5f, 0.5f,  0.0f,
	};

	Niking2D::Ref<Niking2D::VertexBuffer> squareVB;
	squareVB = Niking2D::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

	Niking2D::BufferLayout layout = {
			{Niking2D::ShaderDataType::Float3, "a_Position"},
	};
	squareVB->SetLayout(layout);
	m_SquareVA->AddVertexBuffer(squareVB);

	unsigned int squareIndices[2 * 3] = {
		0,1,2,
		2,3,0
	};
	Niking2D::Ref<Niking2D::IndexBuffer> squareIB;
	squareIB = Niking2D::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int));
	m_SquareVA->SetIndexBuffer(squareIB);



	m_FlatColorShader = Niking2D::Shader::Create("assets/shaders/FlatColor.shader");

	m_Texture = Niking2D::Texture2D::Create("assets/textures/test.png");


}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Niking2D::Timestep ts)
{
	N2_PROFILE_FUNCTION();
	{
		N2_PROFILE_SCOPE("m_CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}


	//	Render
	{
		N2_PROFILE_SCOPE("Render Prep");

		Niking2D::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Niking2D::RenderCommand::Clear();
	}

	{
		N2_PROFILE_SCOPE("Render Draw");

		Niking2D::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Niking2D::Renderer2D::DrawQuad({ 0.0,0.0f }, { 1.0f,1.0f }, { 0.8f,0.2f,0.3f,1.0f });
		Niking2D::Renderer2D::DrawQuad({ 0.5,0.5f, -0.1f }, { 1.0f,1.0f }, m_Texture, 1.0f);


		Niking2D::Renderer2D::DrawQuad({ 0.0,0.0f }, { 1.0f,1.0f }, glm::radians(45.0f), { 0.8f,0.2f,0.3f,1.0f });
		Niking2D::Renderer2D::DrawQuad({ 0.9,0.9f, -0.2f }, { 1.0f,1.0f }, glm::radians(20.0f) , m_Texture, 1.0f);

		Niking2D::Renderer2D::EndScene();
	}
	//Niking2D::Renderer::BeginScene(m_CameraController.GetCamera());
	//m_FlatColorShader->Bind();
	//std::dynamic_pointer_cast<Niking2D::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);


	//Niking2D::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	//Niking2D::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	N2_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	//ImGui::Text("Hello World");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	//for (auto& result : m_ProfileResults) {  
	//	char lable[50];
	//	strcpy(lable, "%.3fms ");
	//	strcat(lable, result.Name);
	//	ImGui::Text(lable, result.Time);
	//}
	//m_ProfileResults.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(Niking2D::Event& event)
{
	m_CameraController.OnEvent(event);
}
