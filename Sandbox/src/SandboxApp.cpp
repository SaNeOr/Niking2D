#include <Niking2D.h>
#include <Niking2D/Core/EntryPoint.h>

#include "ExampleLayer.h"
#include "Sandbox2D.h"

#include "ExampleGame/GameLayer.h"

#include "ExampleScript/ScriptGameLayer.h"


class Sandbox : public Niking2D::Application {
public:
	Sandbox()
	{
		//PushOverLayer(new Niking2D::ImGuiLayer());
		//PushLayer(new ExampleLayer());
		//PushLayer(new Sandbox2D());

		//PushLayer(new GameLayer());
		PushLayer(new ScriptGameLayer());

	}
	
	~Sandbox() {

	}
};


Niking2D::Application* Niking2D::CreateApplication() {
	return new Sandbox();
}