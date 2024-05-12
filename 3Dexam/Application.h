#pragma once
#include <string>
#include <unordered_map>
#include "Mesh.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "CameraInterface.h"
#include "ControllerInterface.h"
#include "EditorCamera.h"
#include "LandscapeMesh.h"

class Application
{
	int SCR_WIDTH = 800, SCR_HEIGHT = 600; // ScreenSize
	GLFWwindow* mWindow = nullptr;

	// -- Using maps to keep classes with multiple objects ordered by name -- //
	std::unordered_map<std::string, Shader*> mShaders; // Map of shaders
	std::unordered_map<std::string, Mesh*> mMeshes; // Map of meshes
public:
	int Setup(); // Start GLFW, GLAD and stuff needed for the window to work.
	int Run(); // Contains the main renderloop and the setup for everything not required for the creation of the window.
	int RenderLoop();
	int Cleanup();

	EditorCamera* editorCamera = nullptr;

	CameraInterface* currentCamera = nullptr;
	ControllerInterface* currentController = nullptr;

	Mesh* GetMesh(std::string name); // Used to get a mesh from the map using a string.
	Shader* GetShader(std::string name); // Used to get a shader from the map using a string.

	void ShaderSetup(); // Used for creating all shaders used in the project.
	void MeshSetup(); // Used for creating all meshes and objects used in the game.
	void MeshBinding();
	void CallbackSetup(); // Called from setup, used to move the callbacks into Application instead of outside main.

	// Callbacks
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void ProcessInput(GLFWwindow* window);

private:
	// -- Utility -- //

	float deltaTime = 0;
	float lastFrame = 0;
	void CalculateDeltaTime();

	bool UseWireframe = false;

	void MoveCurveToSurface(Mesh* CurveMesh, LandscapeMesh* LandscapeMesh, float yOfsett);
};

