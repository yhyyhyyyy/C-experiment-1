@echo off
pushd .

if not exist build (
     md build
)

cd build
cmake -G"MinGW Makefiles" -DCMAKE_POLICY_VERSION_MINIMUM=3.5 ..
mingw32-make.exe

popd
