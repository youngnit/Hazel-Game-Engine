workspace "CoCoCoLa-Game-Engine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    startproject "Application-Sandbox"


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "CoCoCoLa-Game-Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "CoCoCoLa-Game-Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "CoCoCoLa-Game-Engine/vendor/imgui"
IncludeDir["glm"] = "CoCoCoLa-Game-Engine/vendor/glm"
IncludeDir["stb_image"] = "CoCoCoLa-Game-Engine/vendor/stb_image"


include "CoCoCoLa-Game-Engine/vendor/GLFW"
include "CoCoCoLa-Game-Engine/vendor/Glad"
include "CoCoCoLa-Game-Engine/vendor/imgui"


project "CoCoCoLa-Game-Engine"
    location "%{prj.name}"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"
    warnings "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "clpch.h"
    pchsource "CoCoCoLa-Game-Engine/src/clpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
        "%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
    }
    defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
        
    }
    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }
    

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "COLA_PLATFORM_WINDOWS",
            "COLA_BUILD_DLL",
            "_WINDLL"--,
            --"_UNICODE",
            --"UNICODE"
        }     
    
    filter "configurations:Debug"
        defines "COLA_DEBUG"
        runtime "Debug"
        symbols "on"


    filter "configurations:Release"
        defines "COLA_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "COLA_DIST"
        runtime "Release"
        optimize "on"

project "Application-Sandbox"
    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    warnings "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "CoCoCoLa-Game-Engine/src",
        "CoCoCoLa-Game-Engine/vendor/spdlog/include",
        "CoCoCoLa-Game-Engine/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "CoCoCoLa-Game-Engine"
    }

    

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "COLA_PLATFORM_WINDOWS",
            --"COLA_BUILD_DLL"--,
            "_WINDLL"--,
            --"_UNICODE",
            --"UNICODE"
        }

    filter "configurations:Debug"
        defines "COLA_DEBUG"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        defines "COLA_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "COLA_DIST"
        runtime "Release"
		optimize "on"