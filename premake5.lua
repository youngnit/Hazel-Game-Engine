workspace "CoCoCoLa-Game-Engine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "CoCoCoLa-Game-Engine"
    location "%{prj.name}"
    kind "SharedLib"
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
        "%{prj.name}/vendor/spdlog/include"
    }
    
    

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0.22621.0"

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
            ("copy %{wks.location}bin\\" .. outputdir .. "\\%{prj.name}\\%{prj.name}.dll %{wks.location}bin\\" .. outputdir .. "\\Application-Sandbox\\")
        }

        
    
    filter "configurations:Debug"
        defines "COLA_DEBUG"
        symbols "On"
        
    filter "configurations:Release"
        defines "COLA_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "COLA_DIST"
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
        systemversion "10.0.22621.0"

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
        symbols "On"
        
    filter "configurations:Release"
        defines "COLA_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "COLA_DIST"
        optimize "On"
