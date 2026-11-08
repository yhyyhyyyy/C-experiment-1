@echo off
setlocal

call "%~dp0build.bat"
if errorlevel 1 (
    echo Build failed. Tests were not run.
    exit /b 1
)

call "%~dp0run.bat"
set "testResult=%errorlevel%"
if not "%testResult%"=="0" echo Test execution returned a nonzero exit code.
exit /b %testResult%
