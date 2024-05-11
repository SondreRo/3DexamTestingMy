#include "Application.h"

#include <iostream>
#include <glad/glad.h>

#include "MeshGenerator.h"


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

    // Settings
    glEnable(GL_DEPTH_TEST);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    CallbackSetup();

    return 0;
}

int Application::Run()
{
    ShaderSetup();
    MeshSetup();

    // RenderLoop
    RenderLoop();

    Cleanup();
    return 0;
}

int Application::RenderLoop()
{

    while (!glfwWindowShouldClose(mWindow))
    {
        CalculateDeltaTime();
        ProcessInput(mWindow);


    	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);


        // Looping through all meshes and rendering them
        for (auto& mesh : mMeshes)
        {
            mesh.second->Draw();
        }



    	glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
    return 1;
}

int Application::Cleanup()
{
    glfwTerminate();

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

void Application::ShaderSetup()
{
    mShaders["Default"] = new Shader("Triangle.vs", "Triangle.fs");
}

void Application::MeshSetup()
{
    // -- Cube -- //
    Mesh* Cube = new Mesh();
    MeshGenerator::GenerateBox(Cube, glm::vec3(1));
    Cube->transform.SetLocation(glm::vec3(5, 1, 5));
    mMeshes["Cube"] = Cube;



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
    //if (CurrentPlayer)
    //    CurrentPlayer->mouse_callback(window, xpos, ypos);
    //myCamera.mouseCallback(window, xpos, ypos);
}

void Application::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    //if (CurrentPlayer)
    //    CurrentPlayer->MouseButtonCallback(window, button, action, mods);
    //myCamera.MouseButtonCallback(window, button, action, mods);
}

void Application::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    //float newSpeed = myCamera.cameraSpeed + yoffset;
    //newSpeed = glm::clamp(newSpeed, 0.f, 10000.f);
    //myCamera.cameraSpeed = newSpeed;

    //if (CurrentPlayer)
    //    CurrentPlayer->MouseScrollCallback(window, xoffset, yoffset);
}

void Application::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

  /*  if (CurrentPlayer)
        CurrentPlayer->KeyCallback(window, key, scancode, action, mods);

    if (key == GLFW_KEY_T && action == GLFW_PRESS)
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

    if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
    {
        if (CurrentPlayer != nullptr)
        {
            if (UsePlayer)
            {
                UsePlayer = false;
                CurrentPlayer->IsActive = false;
                myCamera.IsActive = true;
            }
            else
            {
                UsePlayer = true;
                CurrentPlayer->IsActive = true;
                myCamera.IsActive = false;
            }

            std::cout << "CurrentPlayer: " << CurrentPlayer->IsActive << std::endl;
            std::cout << "myCamera: " << myCamera.IsActive << std::endl;
        }

    }*/
}

void Application::ProcessInput(GLFWwindow* window)
{
 
  /*  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


    myCamera.processInput(window, deltaTime);
    if (CurrentPlayer)
        CurrentPlayer->ProcessInput(window);

    float Direction = 1;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        Direction = -1;


    if (GetMesh("Landscape"))
    {
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
            GetMesh("Landscape")->transform.AddRotation(glm::vec3(90 * deltaTime * Direction, 0, 0));
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            GetMesh("Landscape")->transform.AddRotation(glm::vec3(0, 90 * deltaTime * Direction, 0));

        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
            GetMesh("Landscape")->transform.AddRotation(glm::vec3(0, 0, 90 * deltaTime * Direction));

        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
            GetMesh("Landscape")->transform.SetRotation(glm::vec3(0, 0, 0));
    }*/





    
}

void Application::CalculateDeltaTime()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
