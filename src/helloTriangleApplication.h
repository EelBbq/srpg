#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <cstdlib>

class helloTraingleApplication{
    public:
        void run();
    
    private:
        GLFWwindow* window;
        VkInstance instance;
    
        void initWindow();
        void initVulkan();
        void createInstance();
        void mainLoop();
        void cleanup();
};
