@echo off

set BUILD_DIR="%~dp0..\build"

if not exist "%BUILD_DIR%" md "%BUILD_DIR%"
pushd "%BUILD_DIR%"
cmake -G "Visual Studio 14 2015" ..
popd
