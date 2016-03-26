@echo off

pushd "%~dp0\.."
git clean -xdf -e vendor
popd
