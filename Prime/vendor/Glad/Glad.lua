
project "Glad"
    kind "StaticLib"
    language "C"
    cppdialect "C++17"
    staticruntime "on"

    targetdir (binDir)
    objdir (objDir)

    files 
    {
        "Glad.lua",
        "include/**.h",
        "src/glad.c"
    }
    

    includedirs
    {
        "include"
    }


    filter {"system:windows", "configurations:*"}
        systemversion "latest"


    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"


    filter "configurations:Release"
        runtime "Release"
        optimize "on"
        symbols "off"