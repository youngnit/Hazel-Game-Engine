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

include "CoCoCoLa-Game-Engine/vendor/GLFW"
include "CoCoCoLa-Game-Engine/vendor/Glad"
include "CoCoCoLa-Game-Engine/vendor/imgui"


project "CoCoCoLa-Game-Engine"
    location "%{prj.name}"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "clpch.h"
    pchsource "CoCoCoLa-Game-Engine/src/clpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }
    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }
    

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "COLA_PLATFORM_WINDOWS",
            "COLA_BUILD_DLL",
            "_WINDLL"--,
            --"_UNICODE",
            --"UNICODE"
        }
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Application-Sandbox/\"")
        }

        
    
    filter "configurations:Debug"
        defines "COLA_DEBUG"
        staticruntime "off"
        runtime "Debug"
        symbols "On"


    filter "configurations:Release"
        defines "COLA_RELEASE"
        staticruntime "off"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "COLA_DIST"
        staticruntime "off"
        runtime "Release"
        optimize "On"

project "Application-Sandbox"
    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"
    


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
        "CoCoCoLa-Game-Engine/vendor/spdlog/include"
    }

    links
    {
        "CoCoCoLa-Game-Engine"
    }

    

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
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
        staticruntime "off"
        runtime "Debug"
        symbols "On"
        
    filter "configurations:Release"
        defines "COLA_RELEASE"
        staticruntime "off"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "COLA_DIST"
        staticruntime "off"
        runtime "Release"
		optimize "On"