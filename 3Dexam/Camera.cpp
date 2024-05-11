#include "Camera.h"

//#include "Application.h"
#include <iostream>

#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include <glm/gtc/type_ptr.hpp>


#include "Shader.h"




void Camera::RecalculateDirections()
{
	cameraRight = glm::normalize(glm::cross(cameraUp, cameraFront));
}

void Camera::RenderFromCamera(Shader shader_program, int winHeight, int winWidth)
{
    if (!IsActive) return;

    RecalculateDirections();
    
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


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

void Camera::processInput(GLFWwindow* window, float dt)
{
    if (!IsActive) return;

    float calcspeed = cameraSpeed * dt; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += calcspeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= calcspeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * calcspeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * calcspeed;

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPos -= glm::normalize(cameraUp) * calcspeed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPos += glm::normalize(cameraUp) * calcspeed;


    /*std::cout << cameraPos.x << " "
        << cameraPos.y << " "
        << cameraPos.z << std::endl;*/

}


void Camera::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (!IsActive) return;

    if (!UseCamera)
    {
        return;
    }

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

void Camera::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    //std::cout << "MouseButtonCallback" << std::endl;
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
