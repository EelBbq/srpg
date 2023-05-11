::-Llibs/glfw/lib-mingw-w64 -lglfw3dll -Llibs/vulkan/Lib -lvulkan-1 -Ilibs/vulkan/include -Ilibs/glfw/include
set libs=
set src=src/*.cpp

g++ -std=c++17 -O2 -o build/game.exe %src% %libs%