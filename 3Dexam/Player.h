#pragma once
#include "Mesh.h"
#include "CameraInterface.h"
#include "ControllerInterface.h"

class GLFWwindow;
class Player : public Mesh, public CameraInterface, public ControllerInterface
{


	glm::vec3 MovementVector = glm::vec3(0);
	glm::vec3 LastLocation = glm::vec3(0);

	float CameraDistance = 5;
	bool firstMouse = true;
	float lastX = 0;
	float lastY = 0;
	float yaw = -90;
	float pitch = 0;
	glm::vec3 cameraFront = glm::vec3(0, 0, -1);
	bool UseCamera = false;
public:

	
	float MovementSpeed = 5.f;
	bool UpdateMovement(float DeltaTime);

	void Tick(float deltaTime) override;

	// -- Camera Interface -- //
	glm::mat4 RenderFromCam(int screenWidth, int screenHeight) override;

	// -- Controller Interface -- //
	void ProcessInput(GLFWwindow* window) override;
	void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos) override;
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) override;
	void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) override;
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
};

