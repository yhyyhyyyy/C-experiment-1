@echo off
setlocal
pushd "%~dp0.."
if errorlevel 1 exit /b 1

cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_POLICY_VERSION_MINIMUM=3.5
if errorlevel 1 (
    echo CMake configuration failed. Build stopped.
    popd
    exit /b 1
)

cmake --build build
set "buildResult=%errorlevel%"
popd
exit /b %buildResult%
