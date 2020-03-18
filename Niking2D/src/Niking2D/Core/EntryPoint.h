#pragma once

#ifdef N2_PLATFORM_WINDOWS
extern Niking2D::Application * Niking2D::CreateApplication();

int main(int argc, char ** argv) {
	Niking2D::Log::Init();
	Niking2D::Script::Init();
	//N2_CORE_TRACE("Initalized Log!");
	//N2_CLIENT_INFO("Hello var = {0} {2}", 1, 5, 10.5);
	//N2_CLIENT_WARN("Hello");



	N2_PROFILE_BEGIN_SESSION("Startup", "Niking2DProfile_Startup.json");
	auto app = Niking2D::CreateApplication();
	N2_PROFILE_END_SESSION();

	N2_PROFILE_BEGIN_SESSION("Runtime", "Niking2DProfile_Runtime.json");
	app->Run();
	N2_PROFILE_END_SESSION();

	N2_PROFILE_BEGIN_SESSION("Shutdown", "Niking2DProfile_Shutdown.json");
  	delete app ;
	N2_PROFILE_END_SESSION();

}

#endif
