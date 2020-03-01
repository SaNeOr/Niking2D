#include <Niking2D.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer :public Niking2D::Layer {
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f),
		m_SquarePosition(0.0f)
	{
		m_VertexArray.reset(Niking2D::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			  0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		};
		Niking2D::Ref <Niking2D::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(Niking2D::VertexBuffer::Create(vertices, sizeof(vertices)));

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
		m_IndexBuffer.reset(Niking2D::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_SquareVA.reset(Niking2D::VertexArray::Create());
		float squareVertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f,	0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,	1.0f, 0.0f,
			 0.5f, 0.5f,  0.0f,	1.0f, 1.0f,
			-0.5f, 0.5f,  0.0f,	0.0f, 1.0f
		};

		Niking2D::Ref<Niking2D::VertexBuffer> squareVB;
		squareVB.reset(Niking2D::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

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

		squareIB.reset(Niking2D::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int)));

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


		std::string textureShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0 ) in vec3 a_Position;
			layout(location = 1 ) in vec2 a_TexCoord;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main(){
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string textureShaderfragSrc = R"(
			#version 330 core
			out vec4 color;

			in vec2 v_TexCoord;
			uniform sampler2D u_Texture;

			void main(){
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		//m_FlatColorShader.reset(Niking2D::Shader::Create(flatShaderVertexSrc, flatShaderfragSrc));


		m_TextureShader.reset(Niking2D::Shader::Create(textureShaderVertexSrc, textureShaderfragSrc));		


		//m_Texture = Niking2D::Texture2D::Create(std::string("assets/textures/tornado.png"));
		m_Texture = Niking2D::Texture2D::Create(std::string("assets/textures/Checkerboard.png"));
		m_testTexture = Niking2D::Texture2D::Create("assets/textures/test.png");
	
		std::dynamic_pointer_cast<Niking2D::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Niking2D::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Niking2D::Timestep ts) override {
		//N2_CLIENT_INFO("ExampleLayer::Update");
		//if (Niking2D::Input::IsKeyPressed(N2_KEY_TAB)) {
		//	N2_CLIENT_TRACE("Tab Key is pressed!");
		//}

		//N2_CORE_TRACE("Delta time :{0}s ({1}ms)", ts.GetSeconds(), ts.GetMillseconds());

		if (Niking2D::Input::IsKeyPressed(N2_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;

		}
		if (Niking2D::Input::IsKeyPressed(N2_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		}
		if (Niking2D::Input::IsKeyPressed(N2_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		}
		if (Niking2D::Input::IsKeyPressed(N2_KEY_UP)) {
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}

		if (Niking2D::Input::IsKeyPressed(N2_KEY_A)) {
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		if (Niking2D::Input::IsKeyPressed(N2_KEY_D)) {
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}




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

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Niking2D::Renderer::BeginScene(m_Camera);

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


		m_Texture->Bind();
		//m_TextureShader->Bind();
		Niking2D::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));	
		
		
		m_testTexture->Bind();
		Niking2D::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Niking2D::Renderer::EndScene();


	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		//ImGui::Text("Hello World");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}


	void OnEvent(Niking2D::Event& event) override {
		//N2_CLIENT_TRACE("{0}", event);
		//if (event.GetEventType() == Niking2D::EventType::KeyPressed) {
		//	Niking2D::KeyPressedEvent& e = (Niking2D::KeyPressedEvent&)event;
		//	N2_CORE_TRACE("{0}", (char)e.GetKeyCode());
		//}


		Niking2D::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Niking2D::KeyPressedEvent>(N2_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));


		 
	}

	bool OnKeyPressedEvent(Niking2D::KeyPressedEvent& event) {
		//if (event.GetKeyCode() == N2_KEY_LEFT) {
		//	m_CameraPosition.x -= m_CameraMoveSpeed;

		//}	
		//if (event.GetKeyCode() == N2_KEY_RIGHT) {
		//	m_CameraPosition.x += m_CameraMoveSpeed;

		//}		
		//if (event.GetKeyCode() == N2_KEY_DOWN) {
		//	m_CameraPosition.y -= m_CameraMoveSpeed;

		//}	
		//if (event.GetKeyCode() == N2_KEY_UP) {
		//	m_CameraPosition.y += m_CameraMoveSpeed;

		//}

		return false;

	}

private:
	Niking2D::Ref<Niking2D::Shader> m_Shader;
	


	Niking2D::Ref<Niking2D::VertexArray> m_VertexArray;
	Niking2D::Ref<Niking2D::Shader> m_FlatColorShader, m_TextureShader;
	Niking2D::Ref<Niking2D::VertexArray> m_SquareVA;

	Niking2D::Ref<Niking2D::Texture2D> m_Texture, m_testTexture;

	Niking2D::OrthograhicCamera m_Camera;
	glm::vec3 m_CameraPosition;

	float m_CameraRotation = 0.0f;

	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotationSpeed = 100.0f;


	glm::vec3 m_SquarePosition;

	float m_SquareMoveSpeed = 1.0f;



	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};





class Sandbox : public Niking2D::Application {
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		//PushOverLayer(new Niking2D::ImGuiLayer());
		
	}
	
	~Sandbox() {

	}
};


Niking2D::Application* Niking2D::CreateApplication() {
	return new Sandbox();
}