binDir = "bin/%{cfg.buildcfg}/%{cfg.system}"
objDir = "bin-obj/%{cfg.buildcfg}/%{cfg.system}"

IncludeDirs = {}
IncludeDirs["spdlog"] = "%{wks.location}/Prime/vendor/spdlog/include"
IncludeDirs["GLFW"] = "%{wks.location}/Prime/vendor/GLFW/include"
IncludeDirs["Glad"] = "%{wks.location}/Prime/vendor/Glad/include"
IncludeDirs["glm"] = "%{wks.location}/Prime/vendor/glm/include"
IncludeDirs["stb"] = "%{wks.location}/Prime/vendor/stb_image/include"
