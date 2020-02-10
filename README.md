# TODO overall:
	seperate out glfw (in progress)
	seperate out a vulkan driver
	get GLFW mouse control and make continue making a seperate Window project
	get a base object with a location and maybe some state?
	seperate StbImage and tinyObj into some kind of resource translation object?

# used resources

resources Used for this project:

glfw:https://www.glfw.org/docs/latest/
vulkan(chunked for ease):https://renderdoc.org/vkspec_chunked/index.html
glm: https://github.com/g-truc/glm/blob/master/manual.md 
	 https://glm.g-truc.net/0.9.9/api/modules.html
stb_image: https://github.com/nothings/stb/blob/master/stb_image.
tinyObj: https://github.com/syoyo/tinyobjloader

I will move these out slowly. Right now Im kinda just building around them so disconnect
concerns (admitedly its done very blindly...)

DESCRIPTOR NONSENSE:

- ok so it seems the way we want to do it is create a descriptor pool and allocate 
 from those. The issue is how do the pools know what they can allocate? I guess what we 
 should try to do is have a Solid descriptor set layout that all shaders will need to obey
 then build the descriptor sets then the descriptor pool (based on http://web.engr.oregonstate.edu/~mjb/cs519v/StudentDiscussions/Hammock_InDepthOverviewOfDescriptors.4pp.pdf)
