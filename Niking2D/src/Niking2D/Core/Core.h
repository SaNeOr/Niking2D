#pragma once
#include <memory>

#ifdef N2_PLATFORM_WINDOWS
#if N2_DYNAMIC_LINK
	#ifdef N2_BUILD_DLL
		#define N2_API __declspec(dllexport)
	#else
		#define N2_API __declspec(dllimport)
	#endif // N2_BUILD DLL
#else
	#define N2_API 
#endif
#else
	#error Niking2D only supports Windows!
#endif // N2_PLATFORM_WINDOWS


#ifdef N2_ENABLE_ASSERTS
	#define N2_ASSERT(x, ...) {if(!(x)) {N2_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define N2_CORE_ASSERT(x, ...) {if(!(x)) {N2_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define N2_ASSERT(x, ...)
	#define N2_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)

#define N2_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


namespace Niking2D {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T>CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}