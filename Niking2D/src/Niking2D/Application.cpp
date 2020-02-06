#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Log.h"

namespace Niking2D {

	Application::Application()
	{

	}
	Application::~Application()
	{

	}
	void Application::Run()
	{

		WindowResizeEvent e(120, 720);
		if (e.IsInCategory(EventCategoryApplication)) {
			N2_CLIENT_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput)) {
			N2_CLIENT_TRACE(e);
		}

		KeyPressedEvent k(2,2);
		if (k.IsInCategory(EventCategoryInput)) {
			N2_CLIENT_TRACE(k);
		}


		
		while (true);

	}
}
