workspace "Niking2D"
	architecture "x86_64"
	startproject "Sandbox"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}


	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir ={}
	IncludeDir["GLFW"] = "Niking2D/vendor/GLFW/include"
	IncludeDir["Glad"] = "Niking2D/vendor/Glad/include"

	-- runs "%{prj.name}/vendor/GLFW/premake5.lua"
	include "Niking2D/vendor/GLFW"
	include "Niking2D/vendor/Glad"

	project "Niking2D"
		location "Niking2D"
		kind "SharedLib"
		language "C++"

		targetdir("bin/" .. outputdir .. "/%{prj.name}")
		objdir("bin-int/" .. outputdir .. "/%{prj.name}")
	
		pchheader "n2pch.h"
		pchsource "%{prj.name}/src/n2pch.cpp"


		files{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		links{
			"GLFW",
			"Glad",
			"opengl32.lib"
		}

		includedirs{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}"
		}

		filter "system:windows"
			cppdialect "c++17"
			staticruntime "on"
			systemversion "latest"

		defines{
	
			"N2_PLATFORM_WINDOWS",
			"N2_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
		filter "configurations:Debug"
			defines "N2_DEBUG"
			buildoptions "/MDd"
			symbols "on"

		filter "configurations:Release"
			defines "N2_RELEASE"
			buildoptions "/MD"
			optimize "on"

		filter "configurations:Dist"
			defines "N2_DIST"
			buildoptions "/MD"
			symbols "on"



	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"

		targetdir("bin/" .. outputdir .. "/%{prj.name}")
		objdir("bin-int/" .. outputdir .. "/%{prj.name}")
	
		files{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs{
			"Niking2D/vendor/spdlog/include",
			"Niking2D/src"
		}

		links{
			"Niking2D"
		}

		filter "system:windows"
			cppdialect "c++17"
			staticruntime "on"
			systemversion "latest"

		defines{
			"N2_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "N2_DEBUG"
			buildoptions "/MDd"
			symbols "on"

		filter "configurations:Release"
			defines "N2_RELEASE"
			buildoptions "/MD"
			optimize "on"

		filter "configurations:Dist"
			defines "N2_DIST"
			buildoptions "/MD"
			symbols "on"
