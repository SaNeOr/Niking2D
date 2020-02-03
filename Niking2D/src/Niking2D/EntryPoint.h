#pragma once

#ifdef N2_PLATFORM_WINDOWS
extern Niking2D::Application * Niking2D::CreateApplication();

int main(int argc, char ** argv) {

	printf("Niking2D\n");
	auto app = Niking2D::CreateApplication();
	app->Run();
	delete app ;
}

#endif
