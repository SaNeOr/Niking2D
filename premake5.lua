workspace "Niking2D"
	architecture "x64"
	startproject "Sandbox"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Niking2D"
	location "Niking2D"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "on"
		systemversion "latest"

	defines{
	
		"N2_PLATFORM_WINDOWS",
		"N2_BUILD_DLL",

	}

	postbuildcommands{

		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")

	}


	filter "configurations:Debug"
		defines "N2_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "N2_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "N2_DIST"
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
		symbols "on"

	filter "configurations:Release"
		defines "N2_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "N2_DIST"
		symbols "on"
