#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Niking2D {
	class N2_API Application
	{
	public:

		Application();
		~Application();

		virtual void Run();
	};



	//	To be defined in CLIENT
	Application* CreateApplication();
}

