#include <Niking2D.h>

#include <Niking2D/Core/EntryPoint.h>


#include "ExampleLayer.h"





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