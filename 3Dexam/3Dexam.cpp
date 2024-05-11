#include "Shader.h"
#include "ShaderFileLoader.h"
#include <iostream>
#include <unordered_map>

#include "BarycentricCalculations.h"
#include "Mesh.h"
#include "LandscapeMesh.h"

#include "MeshGenerator.h"
#include "Camera.h"
#include "Collision.h"
#include "glm/glm.hpp"
#include "Player.h"

void SetupCallbacks(GLFWwindow* window);
// CALLBACKS
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mousebutton_callback(GLFWwindow* window, int button, int action, int mods);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

void processInput(GLFWwindow* window);


// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

std::string vfs = ShaderLoader::LoadShaderFromFile("Triangle.vs");
std::string fs = ShaderLoader::LoadShaderFromFile("Triangle.fs");

Camera myCamera;
Player* CurrentPlayer;


float deltaTime = 0;
float lastFrame = 0;
int main()
{
    //std::cout << "Vfs " << vfs.c_str() << std::endl;
    //std::cout << "fs " << fs.c_str() << std::endl;
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Test Win", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    SetupCallbacks(window);

    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("Triangle.vs", "Triangle.fs"); // you can name your shader files however you like

    Player* myPlayer = new Player();
    meshes["Player"] = myPlayer;
    MeshGenerator::GenerateBox(myPlayer, glm::vec3(1));
    CurrentPlayer = myPlayer;

    LandscapeMesh* m_Landscape = new LandscapeMesh();
    meshes["Landscape"] = m_Landscape;
    MeshGenerator::GenerateLandscape(m_Landscape, 100, 100, 0.5f);
    

    Mesh* m_Cube = new Mesh();
    meshes["Cube"] = m_Cube;
    MeshGenerator::GenerateBox(m_Cube, glm::vec3(1));
    m_Cube->transform.SetLocation(glm::vec3(5, 1, 5));


    for (auto& mesh : meshes)
    {
        mesh.second->Bind();
    }

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        // input
        // -----
        processInput(window);

      

      
        //std::cout << "Height: " << test.x << " " << test.y << " " << test.z << std::endl;
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);



        if (myPlayer)
        {
            if (myPlayer->UpdateMovement(deltaTime))
            {
                glm::vec3 CubeOffsett = glm::vec3(0, -1, 0);
                glm::vec3 FoundCoords = myPlayer->transform.GetLocation();
            	if (BarycentricCalculations::Calculate(m_Landscape, myPlayer->transform.GetLocation() - CubeOffsett, FoundCoords))
                    myPlayer->transform.SetLocationY(FoundCoords.y - CubeOffsett.y);

            }

        }

        
        myCamera.RenderFromCamera(ourShader, SCR_HEIGHT, SCR_WIDTH);
        myPlayer->RenderFromPlayer(ourShader, SCR_HEIGHT, SCR_WIDTH);

        for (auto& mesh : meshes)
        {
           /* if (mesh.first != "Landscape")
            {
                if (SphereCollider::CheckCollision(myCamera.cameraPos, 1, mesh.second->transform.GetLocation(), 1))
                    std::cout << "Collision between cam and " << mesh.first << std::endl;
            }*/
            

            mesh.second->Draw(ourShader);
        }

        if (AABBCollider::CheckCollision(myPlayer->transform.GetLocation(), glm::vec3(2), m_Cube->transform.GetLocation(), glm::vec3(2)))
            std::cout << "Collision " << std::endl;
      
        for (auto& mesh : meshes)
        {
            mesh.second->Draw(ourShader);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    for (auto& mesh : meshes)
    {
        mesh.second->Cleanup();
        delete mesh.second;
    }
    meshes.clear();


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
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
    }

   



}

void SetupCallbacks(GLFWwindow* window)
{
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mousebutton_callback);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetScrollCallback(window, MouseScrollCallback);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    SCR_HEIGHT = height;
    SCR_WIDTH = width;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (CurrentPlayer)
        CurrentPlayer->mouse_callback(window, xpos, ypos);
    myCamera.mouseCallback(window, xpos, ypos);
}

void mousebutton_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (CurrentPlayer)
        CurrentPlayer->MouseButtonCallback(window, button, action, mods);
    myCamera.MouseButtonCallback(window, button, action, mods);
}


bool UseWireframe = false;
bool UsePlayer = true;
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (CurrentPlayer)
        CurrentPlayer->KeyCallback(window, key, scancode, action, mods);

	if (key == GLFW_KEY_T && action == GLFW_PRESS)
    {
	    if(UseWireframe)
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
       
    }
}

void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	float newSpeed = myCamera.cameraSpeed + yoffset;
    newSpeed = glm::clamp(newSpeed, 0.f, 10000.f);
    myCamera.cameraSpeed = newSpeed;

    if (CurrentPlayer)
        CurrentPlayer->MouseScrollCallback(window, xoffset, yoffset);
}
