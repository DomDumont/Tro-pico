if not exist BuildVisual mkdir BuildVisual
cd BuildVisual

cmake  -G "Visual Studio 14 2015 Win64"  -D CMAKE_BUILD_TYPE=Debug ..
cmake --build . --target ALL_BUILD --config Debug
cmake --build . --target package --config Debug

pause

