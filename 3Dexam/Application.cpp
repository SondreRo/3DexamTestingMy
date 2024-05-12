#include "Application.h"
#include <iostream>

#include "BarycentricCalculations.h"
#include "MeshGenerator.h"
#include "Npc.h"
#include "Player.h"
#include "Shader.h"

int Application::Setup()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    mWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Exam2024", NULL, NULL);
    if (mWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(mWindow);
    glfwSetWindowUserPointer(mWindow, this);



    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Settings
    glEnable(GL_DEPTH_TEST);
    glLineWidth(5);
    glPointSize(5);
    CallbackSetup();

    return 0;
}

int Application::Run()
{
    ShaderSetup();
    MeshSetup();
    MeshBinding();
    // RenderLoop
    RenderLoop();

    Cleanup();
    return 0;
}

int Application::RenderLoop()
{
    editorCamera = new EditorCamera();
    currentCamera = editorCamera;
    currentController = editorCamera;

    while (!glfwWindowShouldClose(mWindow))
    {
        CalculateDeltaTime();
        ProcessInput(mWindow);

        //std::cout << "FPS: " << (1 / deltaTime) << std::endl;

    	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        // Tick EditorCamera
        editorCamera->Tick(deltaTime);

        // Loop and tick all meshes.
        for (auto& mesh : mMeshes)
        {
            mesh.second->Tick(deltaTime);
            if (LandscapeMesh* landscape = dynamic_cast<LandscapeMesh*>(mesh.second))
            {
	            if (Player* player = dynamic_cast<Player*>(currentController))
	            {
                    glm::vec3 FoundLoc = player->transform.GetLocation();
                    if (BarycentricCalculations::Calculate(landscape, player->transform.GetLocation() - glm::vec3(0, -1, 0), FoundLoc))
						player->transform.SetLocationY(FoundLoc.y + 1);
	            }
            }
        }

        glm::mat4 camMat{ 1 };
        if (currentCamera) 
            camMat = currentCamera->RenderFromCam(SCR_WIDTH, SCR_HEIGHT);

        // Looping through all meshes and rendering them
        for (auto& mesh : mMeshes)
        {
            
            mesh.second->Draw(camMat);
        }



    	glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
    return 1;
}

int Application::Cleanup()
{
    glfwTerminate();
    return 1;
}

Mesh* Application::GetMesh(std::string name)
{
    if (mMeshes.count(name) > 0)
    {
        return mMeshes[name];
    }
    std::cout << "GetMesh() -- Cant Find mesh with name: '" << name << "'\n";
    return nullptr;
}

Shader* Application::GetShader(std::string name)
{
    if (mShaders.count(name) > 0)
    {
        return mShaders[name];
    }
    std::cout << "GetShader() -- Cant Find shader with name: '" << name << "'\n";
    return nullptr;
}

void Application::ShaderSetup()
{
    mShaders["Default"] = new Shader("Triangle.vs", "Triangle.fs");
}

void Application::MeshSetup()
{

    // -- Landscape -- //
    LandscapeMesh* landscape = new LandscapeMesh();
    landscape->shader = GetShader("Default");
    MeshGenerator::GenerateLandscape(landscape, 100, 100, 0.25);
    landscape->transform.SetLocation(glm::vec3(0));
    mMeshes["landscape"] = landscape;

    // -- Player -- //
    Player* player = new Player();
    player->shader = GetShader("Default");
    MeshGenerator::GenerateBox(player, glm::vec3(0.5f, 1.f, 0.5f));
    mMeshes["player"] = player;

    // -- Player2 -- //
    Player* player2 = new Player();
    player2->shader = GetShader("Default");
    MeshGenerator::GenerateBox(player2, glm::vec3(0.5f, 1.f, 0.5f));
    player2->transform.SetLocation(glm::vec3(5, 0, 0));
    mMeshes["player2"] = player2;

    // -- Curve -- //
    Mesh* curve = new Mesh();
    curve->shader = GetShader("Default");
    MeshGenerator::GenerateCurve(curve, glm::vec3(5,5,5), glm::vec3(20,8,2),glm::vec3(15,3,20), 0.01f);
    mMeshes["curve"] = curve;
    MoveCurveToSurface(curve, landscape,0.2f);

    // -- NPC -- //
    Npc* npc = new Npc();
    npc->shader = GetShader("Default");
    MeshGenerator::GenerateBox(npc, glm::vec3(0.5f, 1.f, 0.5f));
    mMeshes["npc"] = npc;
    npc->pointsToFollow = curve->vertices;
    npc->HeightOfsett = 1;
}

void Application::MeshBinding()
{
	for (auto& mesh : mMeshes)
	{
        std::cout << "Binding mesh: " << mesh.first << std::endl;
        mesh.second->Bind();
	}
}

void Application::CallbackSetup()
{
    glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app)
        {
            app->FramebufferSizeCallback(window, width, height);
        }
        });

    glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xpos, double ypos) {
        auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app) app->MouseMoveCallback(window, xpos, ypos);
        });

    glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods) {
        auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app) app->MouseButtonCallback(window, button, action, mods);
        });

    glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xoffset, double yoffset) {
        auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app) app->MouseScrollCallback(window, xoffset, yoffset);
        });

    glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app) app->KeyCallback(window, key, scancode, action, mods);
        });

}

void Application::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    SCR_HEIGHT = height;
    SCR_WIDTH = width;
}

void Application::MouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (currentController) currentController->MouseMoveCallback(window, xpos, ypos);
}

void Application::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (currentController) currentController->MouseButtonCallback(window, button, action, mods);
}

void Application::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (currentController) currentController->MouseScrollCallback(window, xoffset, yoffset);
}

void Application::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_0 && action == GLFW_PRESS)
    {
        if (UseWireframe)
        {
            UseWireframe = false;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        else
        {
            UseWireframe = true;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
    }





    if (currentController) currentController->KeyCallback(window, key, scancode, action, mods);

    if (action == GLFW_PRESS)
    {
	    switch (key)
	    {
        case (GLFW_KEY_1):
            currentCamera = editorCamera;
            currentController = editorCamera;
            break;
        case(GLFW_KEY_2):
            if (Mesh* player = GetMesh("player"))
            {
                currentCamera = dynamic_cast<CameraInterface*>(player);
                currentController = dynamic_cast<ControllerInterface*>(player);
            }
			break;
        case(GLFW_KEY_3):
            if (Mesh* player = GetMesh("player2"))
            {
                currentCamera = dynamic_cast<CameraInterface*>(player);
                currentController = dynamic_cast<ControllerInterface*>(player);
            }
            break;
	    }
    }
}

void Application::ProcessInput(GLFWwindow* window)
{
    if (currentController) currentController->ProcessInput(window);
}

void Application::CalculateDeltaTime()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Application::MoveCurveToSurface(Mesh* CurveMesh, LandscapeMesh* LandscapeMesh, float yOfsett)
{
    glm::vec3 newPos = glm::vec3(0);
	for (auto& vertex : CurveMesh->vertices)
	{
		if (BarycentricCalculations::Calculate(LandscapeMesh, vertex.Position, newPos))
            vertex.Position.y = newPos.y + yOfsett;
	}
    
}
