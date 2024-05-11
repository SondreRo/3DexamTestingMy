
#include "EditorCamera.h"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"


EditorCamera::EditorCamera()
{
}

void EditorCamera::RecalculateDirections()
{
	cameraRight = glm::normalize(glm::cross(cameraUp, cameraFront));
}

void EditorCamera::Tick(float deltaTime)
{
	
	if (DirectionVector == glm::vec3(0)) return;

	glm::vec3 NormalizedDirection = glm::normalize(DirectionVector);
	glm::vec3 SpeedDirection = NormalizedDirection * cameraSpeed;

	cameraPos = cameraPos + (SpeedDirection * deltaTime);



	DirectionVector = glm::vec3(0);
}

glm::mat4 EditorCamera::RenderFromCam(int screenWidth, int screenHeight)
{
	RecalculateDirections();

	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	float screenWidthf = static_cast<float>(screenWidth);
	float screenHeightf = static_cast<float>(screenHeight);

	float aspect = screenWidthf / screenHeightf;

	aspect = abs(aspect);
	//std::cout << aspect << std::endl;

	glm::mat4 projection = glm::perspective(glm::radians(80.f), aspect, 0.1f, 10000.0f);



	return projection * view;
}

void EditorCamera::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		DirectionVector += cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		DirectionVector -= cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		DirectionVector -= glm::normalize(glm::cross(cameraFront, cameraUp));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		DirectionVector += glm::normalize(glm::cross(cameraFront, cameraUp));

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		DirectionVector -= glm::normalize(cameraUp);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		DirectionVector += glm::normalize(cameraUp);

}

void EditorCamera::MouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (!UseCamera)
	{
		return;
	}

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

void EditorCamera::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			UseCamera = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		if (action == GLFW_RELEASE)
		{
			UseCamera = false;
			firstMouse = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

}

void EditorCamera::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	float newSpeed = cameraSpeed + yoffset;
	newSpeed = glm::clamp(newSpeed, 0.f, 10000.f);
	cameraSpeed = newSpeed;
}
void EditorCamera::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}