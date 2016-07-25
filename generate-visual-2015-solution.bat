if not exist BuildVisual mkdir BuildVisual
cd BuildVisual
cmake -G "Visual Studio 14 2015 Win64" ..
cmake --build .
pause

