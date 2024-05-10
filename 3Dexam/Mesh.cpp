#include "Mesh.h"
#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>

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

void Mesh::Draw(Shader shader)
{
    shader.use();
   
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "meshMat"), 1, GL_FALSE, glm::value_ptr(transform.GetMatrix()));
    glBindVertexArray(VAO);

    if (triangles.size() > 0)
    {
        glDrawElements(GL_TRIANGLES, triangles.size() * 3, GL_UNSIGNED_INT, 0);
    }
    else
    {
       
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        //glDrawArrays(GL_POINTS, 0, vertices.size());
    }

}

void Mesh::Cleanup()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

