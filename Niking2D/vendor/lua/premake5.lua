project "Lua"
    kind "StaticLib"
    language "C++"
    cppdialect "c++17"
    staticruntime "on"
    

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "**.h",
        "**.c",
    }

    removefiles
    {
        "src/luac.c",
        "src/lua.c",
    }
    
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"