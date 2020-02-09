 #include <Niking2D.h>



class ExampleLayer :public Niking2D::Layer {
public:
	ExampleLayer()
		:Layer("Example")
	{

	}

	void OnUpdate() override {
		N2_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Niking2D::Event& event) override {
		N2_CLIENT_TRACE("{0}", event);
	}
};





class Sandbox : public Niking2D::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	
	~Sandbox() {

	}
};


Niking2D::Application* Niking2D::CreateApplication() {
	return new Sandbox();
}