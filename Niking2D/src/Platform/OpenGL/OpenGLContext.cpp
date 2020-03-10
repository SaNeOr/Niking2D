#include "n2pch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include <glad/glad.h>


namespace Niking2D {
	Niking2D::OpenGLContext::OpenGLContext(GLFWwindow * windowHandle)
		:m_WindowHandle(windowHandle)
	{
		N2_PROFILE_FUNCTION();

		N2_CORE_ASSERT(windowHandle, "Window handle is null!");
	}
	void OpenGLContext::Init()
	{
		N2_PROFILE_FUNCTION();


		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		N2_CORE_ASSERT(status, "Failed to initialized Glad!");


		N2_CORE_INFO("OpenGL Info:"); 
		N2_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		N2_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		N2_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));



	}
	void OpenGLContext::SwapBuffers()
	{	
		//N2_PROFILE_FUNCTION();


		glfwSwapBuffers(m_WindowHandle);

	}
}
