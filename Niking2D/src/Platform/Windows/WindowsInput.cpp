#include "n2pch.h"
#include "WindowsInput.h"


#include "Niking2D/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Niking2D {


	Input* Input::s_Instance = new WindowsInput();

	bool Niking2D::WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, keycode);


		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		//return std::pair<float, float>((float)xpos, (float)ypos);
		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		//auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());

		//double xpos, ypos;
		//glfwGetCursorPos(window, &xpos, &ypos);

		//return (float)xpos;

		/*	c++14 below
		auto v = GetMousePositionImpl();
		return std::get<0>(v);
		// */

		auto[x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		//auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());

		//double xpos, ypos;
		//glfwGetCursorPos(window, &xpos, &ypos);

		//return (float)ypos;

		auto[x, y] = GetMousePositionImpl();
		return y;
	}

}
