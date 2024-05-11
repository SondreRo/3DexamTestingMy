#include "Player.h"
#include <glm/gtc/type_ptr.hpp>


void Player::RenderFromPlayer(Shader shader_program, int winHeight, int winWidth)
{
	if (!IsActive) return;

	glm::vec3 cameraPos = transform.GetLocation();
	glm::mat4 view = glm::lookAt(cameraPos + (CameraDistance * -cameraFront), cameraPos, glm::vec3(0,1,0));


	int screenWidth = winWidth;
	int screenHeight = winHeight;

	float screenWidthf = static_cast<float>(screenWidth);
	float screenHeightf = static_cast<float>(screenHeight);

	float aspect = screenWidthf / screenHeightf;

	aspect = abs(aspect);
	//std::cout << aspect << std::endl;

	glm::mat4 projection = glm::perspective(glm::radians(80.f), aspect, 0.1f, 10000.0f);


	unsigned int test1 = glGetUniformLocation(shader_program.ID, "view");
	unsigned int test2 = glGetUniformLocation(shader_program.ID, "projection");
	unsigned int test3 = glGetUniformLocation(shader_program.ID, "viewPos");
	glUniformMatrix4fv(test1, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(test2, 1, GL_FALSE, glm::value_ptr(projection));
	glUniform3fv(test3, 1, glm::value_ptr(cameraPos));
}

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

void Player::ProcessInput(GLFWwindow* window)
{
	if (!IsActive) return;

	glm::vec3 CamFrontFixed = cameraFront;
	CamFrontFixed.y = 0;
	CamFrontFixed = glm::normalize(CamFrontFixed);

	glm::vec3 CamRightFixed = glm::normalize(glm::cross(glm::vec3(0,1,0), cameraFront));
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

void Player::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (!IsActive) return;
}

void Player::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!IsActive) return;

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
	if (!IsActive) return;
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
	if (!IsActive) return;

	float NewDistance = CameraDistance - (float)yoffset;
	CameraDistance = glm::clamp(NewDistance, 0.f, 1000.f);
}
