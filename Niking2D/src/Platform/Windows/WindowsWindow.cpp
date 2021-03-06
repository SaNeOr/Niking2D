#include "n2pch.h"
#include "WindowsWindow.h"
#include "Niking2D/Core/Log.h"
#include "Niking2D/Core/Core.h"


#include "Niking2D/Events/ApplicationEvent.h"
#include "Niking2D/Events/MouseEvent.h"
#include "Niking2D/Events/KeyEvent.h"


#include "Platform/OpenGL/OpenGLContext.h"

namespace Niking2D {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description) {
		N2_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		//N2_PROFILE_FUNCTION();

		Init(props);
	}



	Niking2D::WindowsWindow::~WindowsWindow()
	{
		//N2_PROFILE_FUNCTION();


		ShutDown();
	}

	void WindowsWindow::OnUpdate()
	{
		//N2_PROFILE_FUNCTION();

		glfwPollEvents();

		m_Context->SwapBuffers();

	}

	void WindowsWindow::SetVSync(bool enable)
	{
		//N2_PROFILE_FUNCTION();


		if (enable) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		m_Data.VSync = enable;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::Init(const WindowProps & props)
	{
		//N2_PROFILE_FUNCTION();


		m_Data.Titile = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;



		N2_CORE_INFO("Create Window {0} ({1}, {2})", props.Title, props.Width, props.Height);


		if (!s_GLFWInitialized) {

			int succes = glfwInit();
			N2_CORE_ASSERT(succes, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}


		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Titile.c_str(), nullptr, nullptr);

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();




		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//	Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;  
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});
	
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow * window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});
		


		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}

				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
			
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int c) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			KeyTypedEvent event(c);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods){
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}	

				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
			
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});

		
	}

	void WindowsWindow::ShutDown()
	{
		//N2_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
	}

}


