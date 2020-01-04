#include "Window.h"
#include <stdexcept>

//TODO:
//// get the resize callback working
//static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
//	auto app = reinterpret_cast<HelloTriangleApplication*>(glfwGetWindowUserPointer(window));
//	app->framebufferResized = true;
//}

// make this less specific/create a version that is ESSENTIALLY what GLFW is.
// this is just prep for that sorta
Window::Window(int WIDTH, int HEIGHT) {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	//glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

GLFWwindow* Window::getWindow() {
	return window;
}

bool Window::getWindowClosed()
{
	return !glfwWindowShouldClose(window);
}
 
void Window::destroyWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate(); // maybe mose this else where?
}

void Window::CreateSurface(VkInstance& instance, VkSurfaceKHR& surface)
{
	if (glfwCreateWindowSurface(instance,window, nullptr, &surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::getFrameBufferSize(int* width, int* height)
{
	glfwGetFramebufferSize(window, width, height);
}

void Window::waitEvents()
{
	glfwWaitEvents();
}