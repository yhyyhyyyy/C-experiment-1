@echo off
setlocal
pushd "%~dp0.."
if errorlevel 1 exit /b 1

if not exist "build\tests\training_main.exe" (
    echo training_main.exe does not exist. Build the project first.
    popd
    exit /b 1
)

"%CD%\build\tests\training_main.exe"
set "testResult=%errorlevel%"
popd
exit /b %testResult%
