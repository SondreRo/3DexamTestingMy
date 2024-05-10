#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

struct Vertex
{
	Vertex();


	glm::vec3 Position {0.f };
	glm::vec3 Normal{ 0.f, 1.f, 0.f };
	glm::vec3 Color {1.f};
	

	static void Binding()
	{
		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// color attribute
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	// -- Constructors with types -- //
	Vertex(glm::vec3 inPosition)
	{
		Position = inPosition;
	}

	Vertex(glm::vec3 inPosition, glm::vec3 inNormal)
	{
		Position = inPosition;
		Normal = inNormal;
	}

	Vertex(glm::vec3 inPosition, glm::vec3 inNormal, glm::vec3 inColor)
	{
		Position = inPosition;
		Normal = inNormal;
		Color = inColor;
	}




	// -- Constructors with floats -- //
	Vertex(float posX, float posY, float posZ)
	{
		Position[0] = posX;
		Position[1] = posY;
		Position[2] = posZ;
	}

	Vertex(float posX, float posY, float posZ, float norX, float norY, float norZ)
	{
		Position[0] = posX;
		Position[1] = posY;
		Position[2] = posZ;

		Normal[0] = norX;
		Normal[1] = norY;
		Normal[2] = norZ;
	}


	Vertex(float posX, float posY, float posZ, float norX, float norY, float norZ, float colR, float colG, float colB)
	{
		Position[0] = posX;
		Position[1] = posY;
		Position[2] = posZ;

		Normal[0] = norX;
		Normal[1] = norY;
		Normal[2] = norZ;

		Color[0] = colR;
		Color[1] = colG;
		Color[2] = colB;

	
	}
};
