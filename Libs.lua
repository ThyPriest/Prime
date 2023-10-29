binDir = "bin/%{cfg.buildcfg}/%{cfg.system}"
objDir = "bin-obj/%{cfg.buildcfg}/%{cfg.system}"

IncludeDirs = {}
IncludeDirs["spdlog"] = "%{wks.location}/Prime/vendor/spdlog/include"
