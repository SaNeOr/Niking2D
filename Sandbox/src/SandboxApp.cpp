#include <Niking2D.h>

class Sandbox : public Niking2D::Application {
public:
	Sandbox() {

	}
	
	~Sandbox() {

	}
};


Niking2D::Application* Niking2D::CreateApplication() {
	return new Sandbox();
}