#include "ExampleLayer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


ExampleLayer::ExampleLayer()
	:Layer("Example"), m_Camera(1.6f / 0.9f, true),
	m_SquarePosition(0.0f)
{
	m_VertexArray = Niking2D::VertexArray::Create();

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		  0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};
	Niking2D::Ref <Niking2D::VertexBuffer> m_VertexBuffer;
	m_VertexBuffer = Niking2D::VertexBuffer::Create(vertices, sizeof(vertices));

	{
		Niking2D::BufferLayout layout = {
			{Niking2D::ShaderDataType::Float3, "a_Position"},
			{Niking2D::ShaderDataType::Float4, "a_TexCoord"},
			//{ShaderDataType::Float3, "a_Normal"}
		};
		m_VertexBuffer->SetLayout(layout);
	}


	m_VertexArray->AddVertexBuffer(m_VertexBuffer);

	unsigned int indices[3] = {
		0,1,2
	};
	Niking2D::Ref<Niking2D::IndexBuffer> m_IndexBuffer;
	m_IndexBuffer =  Niking2D::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);

	m_SquareVA = Niking2D::VertexArray::Create();
	float squareVertices[4 * 5] = {
		-0.5f, -0.5f, 0.0f,	0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,	1.0f, 0.0f,
		 0.5f, 0.5f,  0.0f,	1.0f, 1.0f,
		-0.5f, 0.5f,  0.0f,	0.0f, 1.0f
	};

	Niking2D::Ref<Niking2D::VertexBuffer> squareVB;
	squareVB = Niking2D::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

	{
		Niking2D::BufferLayout layout = {
			{Niking2D::ShaderDataType::Float3, "a_Position"},
			{Niking2D::ShaderDataType::Float2, "a_TexCoord"},
		};
		squareVB->SetLayout(layout);
	}
	m_SquareVA->AddVertexBuffer(squareVB);
	unsigned int squareIndices[2 * 3] = {
		0,1,2,
		2,3,0
	};
	Niking2D::Ref<Niking2D::IndexBuffer> squareIB;

	squareIB = Niking2D::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int));

	m_SquareVA->SetIndexBuffer(squareIB);


	std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0 ) in vec3 a_Position;
			layout(location = 1 ) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main(){
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

	std::string fragSrc = R"(
			#version 330 core
			out vec4 color;

			in vec4 v_Color;
			in vec3 v_Position;

			void main(){
				color = vec4(v_Position + 0.5 , 1.0);
				color = v_Color;
				
			}
		)";

	std::string flatShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0 ) in vec3 a_Position;
			layout(location = 1 ) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;



			out vec3 v_Position;
			out vec4 v_Color;

			void main(){
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

	std::string flatShaderfragSrc = R"(
			#version 330 core
			out vec4 color;

			in vec4 v_Color;
			in vec3 v_Position;
			uniform vec3 u_Color;

			void main(){
				color = vec4(v_Position + 0.5 , 1.0);
				color = vec4(u_Color, 1.0);
				
			}
		)";



	//m_FlatColorShader.reset(Niking2D::Shader::Create(flatShaderVertexSrc, flatShaderfragSrc));



	//m_Shader = Niking2D::Shader::Create("VertexPosColorTriangle", vertexSrc, fragSrc);
	//m_TextureShader = Niking2D::Shader::Create("assets/shaders/Texture.shader");
	auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.shader");

	//Niking2D::Shader::Create("filePath");

	//m_Texture = Niking2D::Texture2D::Create(std::string("assets/textures/tornado.png"));
	m_Texture = Niking2D::Texture2D::Create("assets/textures/Checkerboard.png");
	m_testTexture = Niking2D::Texture2D::Create("assets/textures/test.png");

	std::dynamic_pointer_cast<Niking2D::OpenGLShader>(textureShader)->Bind();
	std::dynamic_pointer_cast<Niking2D::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);



}

void ExampleLayer::OnAttach()
{
}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate(Niking2D::Timestep ts)
{
	//N2_CLIENT_INFO("ExampleLayer::Update");
	//if (Niking2D::Input::IsKeyPressed(N2_KEY_TAB)) {
	//	N2_CLIENT_TRACE("Tab Key is pressed!");
	//}

	//N2_CORE_TRACE("Delta time :{0}s ({1}ms)", ts.GetSeconds(), ts.GetMillseconds());



	m_Camera.OnUpdate(ts);

	if (Niking2D::Input::IsKeyPressed(N2_KEY_J)) {
		m_SquarePosition.x -= m_SquareMoveSpeed * ts;

	}
	if (Niking2D::Input::IsKeyPressed(N2_KEY_K)) {
		m_SquarePosition.y -= m_SquareMoveSpeed * ts;
	}

	if (Niking2D::Input::IsKeyPressed(N2_KEY_I)) {
		m_SquarePosition.y += m_SquareMoveSpeed * ts;
	}
	if (Niking2D::Input::IsKeyPressed(N2_KEY_L)) {
		m_SquarePosition.x += m_SquareMoveSpeed * ts;
	}



	Niking2D::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Niking2D::RenderCommand::Clear();



	Niking2D::Renderer::BeginScene(m_Camera.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));


	//std::dynamic_pointer_cast<OpenGLShader>(m_FlatColorShader)->
	//std::dynamic_pointer_cast<OpenGLS
	//m_FlatColorShader->Bind();
	//std::dynamic_pointer_cast<Niking2D::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

	//for(int y = 20; y < 20; y++)
	//	for (int i = 20; i < 20; i++) {
	//		glm::vec3 pos(i * 0.11f, y * 0.11f, 0.0f);

	//		

	//		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) *  glm::translate(glm::mat4(1.0f), m_SquarePosition) * scale;
	//		Niking2D::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);

	//	}

	auto textureShader = m_ShaderLibrary.Get("Texture");

	m_Texture->Bind();
	Niking2D::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


	m_testTexture->Bind();
	Niking2D::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Niking2D::Renderer::EndScene();


}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	//ImGui::Text("Hello World");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void ExampleLayer::OnEvent(Niking2D::Event & event)
{
	//N2_CLIENT_TRACE("{0}", event);
	//if (event.GetEventType() == Niking2D::EventType::KeyPressed) {
	//	Niking2D::KeyPressedEvent& e = (Niking2D::KeyPressedEvent&)event;
	//	N2_CORE_TRACE("{0}", (char)e.GetKeyCode());
	//}

	m_Camera.OnEvent(event);

	Niking2D::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Niking2D::KeyPressedEvent>(N2_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));



}