#include "n2pch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include <glad/glad.h>


namespace Niking2D {
	Niking2D::OpenGLContext::OpenGLContext(GLFWwindow * windowHandle)
		:m_WindowHandle(windowHandle)
	{
		N2_CORE_ASSERT(windowHandle, "Window handle is null!");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		N2_CORE_ASSERT(status, "Failed to initialized Glad!");
	}
	void OpenGLContext::SwapBuffers()
	{	
		


		glfwSwapBuffers(m_WindowHandle);

	}
}
