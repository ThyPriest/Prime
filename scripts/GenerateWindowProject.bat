@echo off
pushd %~dp0\..\
call premake\premake5.exe vs2022 --file="Build.lua"
popd
PAUSE