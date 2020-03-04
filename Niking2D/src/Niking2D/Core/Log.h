#pragma once


#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "Core.h"

namespace Niking2D {

	class N2_API Log
	{

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
			return s_CoreLogger;
		}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {
			return s_ClientLogger;
		}		
		



	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}


//	Core log macros
#define N2_CORE_TRACE(...)	::Niking2D::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define N2_CORE_INFO(...)	::Niking2D::Log::GetCoreLogger()->info(__VA_ARGS__)
#define N2_CORE_WARN(...)	::Niking2D::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define N2_CORE_ERROR(...)	::Niking2D::Log::GetCoreLogger()->error(__VA_ARGS__)


//	Client log macros

#define N2_CLIENT_TRACE(...)	::Niking2D::Log::GetClientLogger()->trace(__VA_ARGS__)
#define N2_CLIENT_INFO(...)	::Niking2D::Log::GetClientLogger()->info(__VA_ARGS__)
#define N2_CLIENT_WARN(...)	::Niking2D::Log::GetClientLogger()->warn(__VA_ARGS__)
#define N2_CLIENT_ERROR(...)	::Niking2D::Log::GetClientLogger()->error(__VA_ARGS__)
