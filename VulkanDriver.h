#ifndef VULKAN_DRIVER_HPP
#define VULKAN_DRIVER_HPP

#include <vector>
#include <optional>
#include "Window.h"

//TODO:
// Figure out every part of the tutorial that
// theoretically shouldn't be attached to an object
// and remove it.
// This means any pools get removed and put here
// any vulkan instance initialization will be here 
// and I wanna say present and swapchain shenanigans will run
// through here.
// though maybe not discriptor set pools? Seems like those are dependent
// more so on the descriptor themselves. Weird why.
// for those make an array for loading different objects. Might need a dirty
// manual labor intensive system for figuring this out.

// Graphics pipeline == fixed function state + shaders
//	- this also has a dependency on set layout (yay) which means we probably are going 
//	to make a system for building the graphics pipeline in a seperate class.

// What I'm probably going to have to do is set up some getters and setters here
// and then when I issue a draw figure out as much as I can cache and what I will 
// need to reconstruct (the answer is probably of cacheing). I can cache pipelines which 
// kind of means I can cache a bunch of other stuff. It also means that the game objects probably
// will 
struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};


class VulkanDriver
{
public:
	VulkanDriver(Window window); // initialize the vulkan instance.
	~VulkanDriver();

private:
	void createInstance();		// initilizes vulkan instance
	void setupDebugMessenger(); // sets up debug messages
	void createSurface();		// surface for presentation
	void pickPhysicalDevice();	// pick physical device
	void createLogicalDevice(); // create the logical device
	void createSwapChain();		// create swap chain
	void createSwapChainViews();// create swap chain image views
	void createCommandPool();	// create the command pool
	void createCommandBuffers();// create command buffers

	// color attachment for framebuffer/renderpass.
	// these will need to be moved to a different class most
	// likely as different renderpasses are gonna need different ones.
	void createColorResources();
	void createDepthResources();
	void createFramebuffers();	

	//helpers (go through the cpp and make sure these all of them
	//have been added to this. 
	VkSampleCountFlagBits   getMaxUsableSampleCount();
	QueueFamilyIndices	    findQueueFamilies(VkPhysicalDevice device);
	bool				    isDeviceSuitable(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkExtent2D				chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	
	
	//Members
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	Window* mRenderwindow;

	
	VkSurfaceKHR mSurface;



	VkPhysicalDevice mPhysicalDevice = VK_NULL_HANDLE;
	VkDevice device;

	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;


	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	std::vector<VkFence> imagesInFlight;

	size_t currentFrame = 0;

	bool framebufferResized = false;
};

#endif