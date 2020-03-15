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
	IncludeDir["ImGui"]= "Niking2D/vendor/imgui"
	IncludeDir["glm"]  = "Niking2D/vendor/glm"
	IncludeDir["stb_image"] = "Niking2D/vendor/stb_image"
	IncludeDir["lua"] = "Niking2D/vendor/lua/src"
	IncludeDir["sol"] = "Niking2D/vendor/sol"

	-- runs "%{prj.name}/vendor/GLFW/premake5.lua"
	include "Niking2D/vendor/GLFW"
	include "Niking2D/vendor/Glad"
	include "Niking2D/vendor/imgui"
	include "Niking2D/vendor/lua"

	project "Niking2D"
		location "Niking2D"
		kind "StaticLib"
		language "C++"
		cppdialect "c++17"
		staticruntime "on"


		targetdir("bin/" .. outputdir .. "/%{prj.name}")
		objdir("bin-int/" .. outputdir .. "/%{prj.name}")
	
		pchheader "n2pch.h"
		pchsource "%{prj.name}/src/n2pch.cpp"


		files{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/vendor/stb_image/**.h",
			"%{prj.name}/vendor/stb_image/**.cpp",
			"%{prj.name}/vendor/sol/**.hpp",
			"%{prj.name}/vendor/glm/glm/**.hpp",
			"%{prj.name}/vendor/glm/glm/**.inl",
		}

		links{
			"GLFW",
			"Glad",
			"ImGui",
			"opengl32.lib",
			"Lua",
		}

		includedirs{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{prj.name}/vendor",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb_image}",
			"%{IncludeDir.lua}",
			"%{IncludeDir.sol}",

		}

		filter "system:windows"
			staticruntime "on"
			systemversion "latest"

		defines{
	
			"N2_PLATFORM_WINDOWS",
			"N2_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		filter "configurations:Debug"
			defines "N2_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "N2_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "N2_DIST"
			runtime "Release"
			symbols "on"



	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "c++17"
		staticruntime "on"
		

		targetdir("bin/" .. outputdir .. "/%{prj.name}")
		objdir("bin-int/" .. outputdir .. "/%{prj.name}")
	
		files{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs{
			"Niking2D/vendor/spdlog/include",
			"Niking2D/vendor/imgui",
			"Niking2D/src",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb_image}",
			"%{IncludeDir.lua}",
			"%{IncludeDir.sol}",

		}


		links{
			"Niking2D",
		}

		filter "system:windows"
			staticruntime "on"
			systemversion "latest"

		defines{
			"N2_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "N2_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "N2_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "N2_DIST"
			runtime "Release"
			symbols "on"
