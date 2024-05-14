#pragma once
#include "CameraInterface.h"
#include "ControllerInterface.h"
#include "glm/glm.hpp"

class Shader;
struct GLFWwindow;

class EditorCamera : public CameraInterface, public ControllerInterface{

	bool firstMouse = true;
	double lastX{ 0 }, lastY{ 0 };

	bool UseCamera = false;

public:
	EditorCamera();
	float cameraSpeed = 4;
	glm::vec3 cameraPos = glm::vec3(3.0f, 0.0f, 5.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraFront));

	float yaw = -90;
	float pitch = 0;

	void RecalculateDirections();

	void Tick(float deltaTime);
	glm::vec3 DirectionVector = glm::vec3(0);

	// -- Camera Interface -- //
	glm::mat4 RenderFromCam(int screenWidth, int screenHeight, glm::vec3& camPos) override;

	// -- Controller Interface -- //
	void ProcessInput(GLFWwindow* window) override;
	void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos) override;
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) override;
	void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) override;
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;

};
