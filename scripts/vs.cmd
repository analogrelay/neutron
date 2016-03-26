@echo off

call "%~dp0cmake_gen.cmd"

devenv "%~dp0..\build\neutron.sln"
