#pragma once


#ifdef N2_PLATFORM_WINDOWS
	#ifdef N2_BUILD_DLL
		#define N2_API __declspec(dllexport)
	#else
		#define N2_API __declspec(dllimport)
	#endif // N2_BUILD DLL

#else
	#error Niking2D only supports Windows!
#endif // N2_PLATFORM_WINDOWS
