#pragma once
// Wraper for glfw so we can isolate and replace when needed later.
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
class Window
{

public:
	Window(int WIDTH, int HEIGHT);
	GLFWwindow* getWindow();
	bool getWindowClosed();
	void destroyWindow();
	void CreateSurface(VkInstance& instance, VkSurfaceKHR& surface);
	void PollEvents();
	void getFrameBufferSize(int* width, int* height);
	void waitEvents();
private:
	GLFWwindow* window;
};

