#include <Niking2D.h>



class ExampleLayer :public Niking2D::Layer {
public:
	ExampleLayer()
		:Layer("Example")
	{

	}

	void OnUpdate() override {
		//N2_CLIENT_INFO("ExampleLayer::Update");

		if (Niking2D::Input::IsKeyPressed(N2_KEY_TAB)) {
			N2_CLIENT_TRACE("Tab Key is pressed!");
		}
	}

	void OnEvent(Niking2D::Event& event) override {
		//N2_CLIENT_TRACE("{0}", event);
		if (event.GetEventType() == Niking2D::EventType::KeyPressed) {
			Niking2D::KeyPressedEvent& e = (Niking2D::KeyPressedEvent&)event;
			N2_CORE_TRACE("{0}", (char)e.GetKeyCode());
		}

		 
	}
};





class Sandbox : public Niking2D::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		//PushOverLayer(new Niking2D::ImGuiLayer());
		
	}
	
	~Sandbox() {

	}
};


Niking2D::Application* Niking2D::CreateApplication() {
	return new Sandbox();
}