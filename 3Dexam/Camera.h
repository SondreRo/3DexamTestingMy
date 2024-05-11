#pragma once
#include "glm/glm.hpp"


class Shader;
struct GLFWwindow;

class Camera {

	bool firstMouse = true;
	double lastX{ 0 }, lastY{ 0 };

	bool UseCamera = false;

public:
	bool IsActive = false;
	float cameraSpeed = 4;
	glm::vec3 cameraPos = glm::vec3(3.0f, 0.0f, 5.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraFront));

	float yaw = -90;
	float pitch = 0;

	void RecalculateDirections();
	void RenderFromCamera(Shader shader_program, int winHeight, int winWidth);
	void processInput(GLFWwindow* window, float dt);
	void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};
