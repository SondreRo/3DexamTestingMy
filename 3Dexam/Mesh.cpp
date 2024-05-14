#include "Mesh.h"

#include <iostream>
#include "Shader.h"

#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh()
{
    material = new Material();
}

Mesh::~Mesh()
{
}

void Mesh::AABB_CollisionResponse()
{
}

void Mesh::Bind()
{
   
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glGenBuffers(1, &EBO);


    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(Triangle), triangles.data(), GL_STATIC_DRAW);

    Vertex::Binding();



}

void Mesh::Draw(glm::mat4 CamMat, glm::vec3 CamPos)
{
    if (hidden) return;

    if (!shader)
    {
        std::cout << "No shader found for Mesh" << std::endl;
    	return;
    }
    shader->use();

    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "camMat"), 1, GL_FALSE, glm::value_ptr(CamMat));


    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "meshMat"), 1, GL_FALSE, glm::value_ptr(transform.GetMatrix()));
    glBindVertexArray(VAO);

    unsigned int CamPosPos = glGetUniformLocation(shader->ID, "viewPos");
    glUniform3fv(CamPosPos, 1, glm::value_ptr(CamPos));


    if (texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture->ID);
        shader->setInt("useTexture", 1);
        //std::cout << "rendering texture\n";

    }
    else
    {
        shader->setInt("useTexture", 0);
        glBindTexture(GL_TEXTURE_2D, 0);

    }

    unsigned int tempDrawType = 0;

    switch (meshType)
    {
    case(mt_Triangle):
        tempDrawType = GL_TRIANGLES;
        break;
    case(mt_Line):
        tempDrawType = GL_LINE_STRIP;
        break;

    case(mt_Dot):
    	tempDrawType = GL_POINTS;
    	break;
    default:
        tempDrawType = GL_TRIANGLES;
        break;
    }

    if (material)
    {
        material->UseMaterial(shader);
    }

    if (triangles.size() > 0)
    {
        glDrawElements(tempDrawType, triangles.size() * 3, GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(tempDrawType, 0, vertices.size());
       
    }

}

void Mesh::Tick(float deltaTime)
{
    AABB_Position = transform.GetLocation();
}

void Mesh::Cleanup()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

