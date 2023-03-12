#-lXxf86vm -lXi
#-ldl -lpthread -lX11 -lXrandr
#-lglfw -lvulkan -ldl -lpthread -lX11 -lXrandr
#-L/mnt/c/msys64/mingw64/lib


CFLAGS = -std=c++17 -O2
#LDFLAGS = -lgdi32 -luser32 -lkernel32 -Llibs/glfw/lib-mingw-w64 -lglfw3 -Llibs/vulkan/Lib -lvulkan-1 -Ilibs/vulkan/include -Ilibs/glfw/include 
#LDFLAGS = -Llibs/glfw/lib-mingw-w64 -lglfw3 -Llibs/vulkan/Lib -lvulkan-1 -Ilibs/vulkan/include -Ilibs/glfw/include 
LDFLAGS = -Llibs/glfw/lib-mingw-w64 -lglfw3dll -Llibs/vulkan/Lib -lvulkan-1 -Ilibs/vulkan/include -Ilibs/glfw/include 
LXFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXrandr -Ilibs/vulkan/include -Ilibs/glfw/include 
SRC = src/main.cpp


VulkanTest: src/main.cpp
	x86_64-w64-mingw32-g++ $(CFLAGS) -o build/VulkanTest.exe $(SRC) $(LDFLAGS)
	

.PHONY: test clean

test: VulkanTest
	./build/VulkanTest.exe

clean:
	rm -f ./build/VulkanTest.exe

lmake: src/main.cpp
	g++ $(CFLAGS) -o build/VulkanTest $(SRC) $(LXFLAGS)

.PHONY: ltest lclean

ltest:
	./build/VulkanTest

lclean:
	rm -f ./build/VulkanTest