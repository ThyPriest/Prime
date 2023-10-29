include "Libs.lua"

workspace "Prime"
    architecture "x64"
    startproject "Terra"
    warnings "off"
    externalwarnings "off"


    configurations
    {
        "Debug",
        "Release"
    }


    flags
    {
        "MultiProcessorCompile"
    }

    
    group "Core"
        include "Prime/Prime.lua"
        include "Terra/Terra.lua"
    group ""


    group "Dependencies"
        include "Prime/vendor/GLFW/GLFW.lua"
        include "Prime/vendor/Glad/Glad.lua"
    group ""

