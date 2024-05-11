#pragma once
#include "Mesh.h"
class Player : public Mesh
{


	glm::vec3 MovementVector = glm::vec3(0);
	glm::vec3 LastLocation = glm::vec3(0);

	float CameraDistance = 5;
	bool firstMouse = true;
	float lastX = 0;
	float lastY = 0;
	float yaw = 0;
	float pitch = 0;
	glm::vec3 cameraFront = glm::vec3(0, 0, -1);
	bool UseCamera = false;
public:

	bool IsActive = true;

	void RenderFromPlayer(Shader shader_program, int winHeight, int winWidth);
	float MovementSpeed = 5.f;
	bool UpdateMovement(float DeltaTime);

	void ProcessInput(GLFWwindow* window);
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

