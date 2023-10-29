
project "Prime"
    kind "SharedLib"
    language  "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/".. binDir .. "/%{prj.name}")
    objdir ("%{wks.location}/".. objDir .. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "Source/pch.cpp"

    
    files
    {
        "Prime.lua",
        "Source/**.h",
        "Source/**.cpp",
    }


    includedirs
    {
        "Source",
        "%{IncludeDirs.spdlog}",
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.Glad}"
    }


    links
    {
        "GLFW", "Glad"
    }


    postbuildcommands
    {
        
        "python "  .. "%{wks.location}/scripts" .. "/Postbuild.py"
    }


    filter {"system:windows", "configurations:*"}
        systemversion "latest"

        defines
        {
            "PRIME_BUILD_DLL",
            "PRIME_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }


    filter {"system:linux", "configurations:*"}
        defines
        {
            "PRIME_PLATFORM_LINUX"
        }


    filter {"system:macosx", "configurations:*"}
        defines
        {
            "PRIME_PLATFORM_MACOSX"
        }


    filter "configurations:Debug"
        defines
        {
            "PRIME_DEBUG"
        }

        runtime "Debug"
        symbols "on"


    filter "configurations:Release"
        defines
        {
            "PRIME_RELEASE"
        }

        runtime "Release"
        symbols "off"
        optimize "on"