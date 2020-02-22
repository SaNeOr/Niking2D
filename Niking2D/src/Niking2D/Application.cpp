#include "n2pch.h"
#include "Application.h"

#include "Events/KeyEvent.h"
#include "Log.h"
#include <glad/glad.h>

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Niking2D {

	Application* Application::s_Instance = nullptr;



	Application::Application()
	{
		N2_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = (std::unique_ptr<Window>) Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();

		PushOverLayer(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			  0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		};
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		{
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"},
				//{ShaderDataType::Float3, "a_Normal"}
			};
			m_VertexBuffer->SetLayout(layout);
		}


		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3] = {
			0,1,2
		};
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_SquareVA.reset(VertexArray::Create());
		float squareVertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f, 0.5f,  0.0f,
			-0.5f, 0.5f,  0.0f,
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		{
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
			};
			squareVB->SetLayout(layout);
		}
		m_SquareVA->AddVertexBuffer(squareVB);
		unsigned int squareIndices[2*3] = {
			0,1,2,
			2,3,0
		};
		std::shared_ptr<IndexBuffer> squareIB;
		
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int)));
		
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0 ) in vec3 a_Position;
			layout(location = 1 ) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main(){
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
				v_Color = a_Color;
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
		
		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0 ) in vec3 a_Position;
			layout(location = 1 ) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main(){
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
				v_Color = a_Color;
			}
		)";

		std::string blueShaderfragSrc = R"(
			#version 330 core
			out vec4 color;

			in vec4 v_Color;
			in vec3 v_Position;

			void main(){
				color = vec4(v_Position + 0.5 , 1.0);
				color = vec4(0.2, 0.3, 0.8, 1.0);
				
			}
		)";
		   
		m_Shader.reset(new Shader(vertexSrc, fragSrc));
		m_BludeShader.reset(new Shader(blueShaderVertexSrc, blueShaderfragSrc));

 	}



	Application::~Application()
	{

	}
	void Application::Run()
	{

		while (m_Running) {

			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_SquareVA->Bind();
			m_BludeShader->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);


			

		/*	for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}*/

			m_ImGuiLayer->Begin();

  			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}

			m_ImGuiLayer->End();
			
			//auto[x, y] = Input::GetMousePosition();
			//N2_CORE_TRACE("{0}, {1}", x, y);

			//m_ImGuiLayer->Begin();
			//	for (Layer* layer : m_LayerStack) {
			//		layer->OnUpdate();
			//	}
			//m_ImGuiLayer->End();
				


			m_Window->OnUpdate();
		}

	}
	void Application::OnEvent(Event & e)
	{

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		//N2_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLayer(Layer* layer)
	{
		m_LayerStack.PushOverLayer(layer);
		layer->OnAttach();
	}
}