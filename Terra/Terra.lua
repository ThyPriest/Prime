
project "Terra"
    kind "ConsoleApp"
    language  "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/".. binDir .. "/%{prj.name}")
    objdir ("%{wks.location}/".. objDir .. "/%{prj.name}")


    files
    {
        "Terra.lua",
        "Source/**.h",
        "Source/**.cpp"
    }


    includedirs
    {
        "%{wks.location}/Prime/Source",
        "%{IncludeDirs.spdlog}",
        "%{IncludeDirs.glm}"
    }


    links
    { 
        "Prime"
    }


    filter {"system:windows", "configurations:*"}
        systemversion "latest"

        defines
        {
            "PRIME_PLATFORM_WINDOWS"
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