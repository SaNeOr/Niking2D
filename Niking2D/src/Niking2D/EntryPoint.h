#pragma once

#ifdef N2_PLATFORM_WINDOWS
extern Niking2D::Application * Niking2D::CreateApplication();

int main(int argc, char ** argv) {
	Niking2D::Log::Init();
	N2_CORE_TRACE("Initalized Log!");
	N2_CLIENT_INFO("Hello");
	N2_CLIENT_INFO("Hello var = {0} {2}", 1, 5, 10.5);
	N2_CLIENT_INFO("Hello");
	N2_CLIENT_WARN("Hello");


	//printf("Niking2D\n");
	auto app = Niking2D::CreateApplication();
	app->Run();
  	delete app ;
}

#endif
