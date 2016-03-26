@echo off


pushd "%~dp0\.."
if "%1"=="-f" (
    git clean -xdf -e vendor
) else (
    git clean -xdn -e vendor
)
popd
