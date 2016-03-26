@echo off

set BUILD_DIR="%~dp0..\build"

call "%~dp0cmake_gen.cmd"
devenv "%BUILD_DIR%\Project.sln"
