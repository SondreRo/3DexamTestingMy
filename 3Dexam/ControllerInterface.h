#pragma once
struct GLFWwindow;
class ControllerInterface
{
public:
	virtual ~ControllerInterface() = default;
	virtual void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
	{
		
	}
	virtual void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		
	}
	virtual void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		
	}
	virtual void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		
	}
	virtual void ProcessInput(GLFWwindow* window)
	{
		
	}
};

