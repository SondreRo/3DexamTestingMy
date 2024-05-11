#include "Player.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include "Shader.h"

bool Player::UpdateMovement(float DeltaTime)
{
	//MovementVector = glm::normalize(MovementVector);
	transform.AddLocation(MovementVector * MovementSpeed * DeltaTime);
	MovementVector = glm::vec3(0);

	if (LastLocation != transform.GetLocation())
	{
		LastLocation = transform.GetLocation();
		return true;
	}
	else
	{
		return false;
	}

}

void Player::Tick(float deltaTime)
{
	Mesh::Tick(deltaTime);
	UpdateMovement(deltaTime);
}

glm::mat4 Player::RenderFromCam(int screenWidth, int screenHeight)
{
	glm::vec3 cameraPos = transform.GetLocation();
	glm::mat4 view = glm::lookAt(cameraPos + (CameraDistance * -cameraFront), cameraPos, glm::vec3(0, 1, 0));

	float screenWidthf = static_cast<float>(screenWidth);
	float screenHeightf = static_cast<float>(screenHeight);

	float aspect = screenWidthf / screenHeightf;

	aspect = abs(aspect);
	//std::cout << aspect << std::endl;

	glm::mat4 projection = glm::perspective(glm::radians(80.f), aspect, 0.1f, 10000.0f);

	return projection * view;
}

void Player::ProcessInput(GLFWwindow* window)
{
	glm::vec3 CamFrontFixed = cameraFront;
	CamFrontFixed.y = 0;
	CamFrontFixed = glm::normalize(CamFrontFixed);

	glm::vec3 CamRightFixed = glm::normalize(glm::cross(glm::vec3(0, 1, 0), cameraFront));
	// Movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		MovementVector += CamFrontFixed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		MovementVector -= CamFrontFixed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		MovementVector += CamRightFixed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		MovementVector -= CamRightFixed;
}

void Player::MouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (!UseCamera) return;

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

void Player::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
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

void Player::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	float NewDistance = CameraDistance - (float)yoffset;
	CameraDistance = glm::clamp(NewDistance, 0.f, 1000.f);
}

void Player::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}
