#include "MeshGenerator.h"
#include <iostream>

#include "CollisionCalculation.h"


float MeshGenerator::Function(float x, float z)
{
	return (cos(x) + cos(z));
}

glm::vec3 MeshGenerator::CalcNormal(Vertex& p1, Vertex& p2, Vertex& p3)
{
	glm::vec3 V1 = p2.Position - p1.Position;
	glm::vec3 V2 = p3.Position - p1.Position;

	glm::vec3 cross = glm::cross(V2, V1);

	//std::cout << "Normal X: " << cross.x << " y: " << cross.y << " z: " << cross.z << std::endl;
	p1.Normal =+ glm::normalize(cross);
	p2.Normal =+ glm::normalize(cross);
	p3.Normal =+ glm::normalize(cross);
	return glm::normalize(cross);
}

void MeshGenerator::GenerateBox(Mesh* inMesh, glm::vec3 Size)
{
	
	std::vector<Vertex> tempVertex;

	Size /= 2;

	tempVertex.emplace_back(glm::vec3(-Size.x, -Size.y, Size.z), glm::vec3(-Size.x, -Size.y, Size.z), glm::vec3(-Size.x, -Size.y, Size.z));
	tempVertex.emplace_back(glm::vec3(Size.x, -Size.y, Size.z), glm::vec3(Size.x, -Size.y, Size.z), glm::vec3(Size.x, -Size.y, Size.z));
	tempVertex.emplace_back(glm::vec3(Size.x, Size.y, Size.z), glm::vec3(Size.x, Size.y, Size.z), glm::vec3(Size.x, Size.y, Size.z));
	tempVertex.emplace_back(glm::vec3(-Size.x, Size.y, Size.z), glm::vec3(-Size.x, Size.y, Size.z), glm::vec3(-Size.x, Size.y, Size.z));

	tempVertex.emplace_back(glm::vec3(Size.x, -Size.y, -Size.z), glm::vec3(Size.x, -Size.y, -Size.z) ,glm::vec3(Size.x, -Size.y, -Size.z));
	tempVertex.emplace_back(glm::vec3(-Size.x, -Size.y, -Size.z), glm::vec3(-Size.x, -Size.y, -Size.z),glm::vec3(-Size.x, -Size.y, -Size.z));
	tempVertex.emplace_back(glm::vec3(-Size.x, Size.y, -Size.z), glm::vec3(-Size.x, Size.y, -Size.z), glm::vec3(-Size.x, Size.y, -Size.z));
	tempVertex.emplace_back(glm::vec3(Size.x, Size.y, -Size.z), glm::vec3(Size.x, Size.y, -Size.z), glm::vec3(Size.x, Size.y, -Size.z));

	inMesh->vertices = tempVertex;

	// Front face
	inMesh->triangles.emplace_back(0, 1, 2);
	inMesh->triangles.emplace_back(2, 3, 0);

	// Back face
	inMesh->triangles.emplace_back(4, 5, 6);
	inMesh->triangles.emplace_back(6, 7, 4);

	// Left face
	inMesh->triangles.emplace_back(5, 0, 3);
	inMesh->triangles.emplace_back(3, 6, 5);

	// Right face
	inMesh->triangles.emplace_back(1, 4, 7);
	inMesh->triangles.emplace_back(7, 2, 1);

	// Top face
	inMesh->triangles.emplace_back(3, 2, 7);
	inMesh->triangles.emplace_back(7, 6, 3);

	// Bottom face
	inMesh->triangles.emplace_back(5, 4, 1);
	inMesh->triangles.emplace_back(1, 0, 5);
	inMesh->meshType = Mesh::mt_Triangle;

	if (AABBCollisionInterface* collider = dynamic_cast<AABBCollisionInterface*>(inMesh))
	{
		collider->AABB_Position = inMesh->transform.GetLocation();
		collider->AABB_Size = Size;//* 2.f;
		collider->AABB_Enabled = true;
		std::cout << "Added AABB to mesh" << std::endl;
	}

}

void MeshGenerator::GenerateLandscape(LandscapeMesh* inMesh, int xCount, int zCount, float stepSize)
{
	inMesh->xCount = xCount;
	inMesh->zCount = zCount;
	inMesh->StepSize = stepSize;

	// Calculate Vertices
	for (int x = 0; x < xCount; x++)
	{
		for (int z = 0; z < zCount; z++)
		{
			float xCoord = x * stepSize;
			float zCoord = z * stepSize;

			float yCoord = Function(xCoord, zCoord);

			float Color = glm::clamp((yCoord + 1) /2, 0.f, 1.f);

			Vertex newVertex(xCoord, yCoord, zCoord);
			newVertex.Color = glm::vec3(Color, Color, Color);

			inMesh->vertices.emplace_back(newVertex);
		}
	}


	// Calculate Indices and Normals
	for (int x = 0; x < xCount - 1; x++)
	{
		if ((x & 1) == 0)
		{
			for (int z = 0; z < zCount - 1; z++)
			{
				unsigned int p1 = (p1 = x + (z * xCount));
				unsigned int p2 = (p2 = x + ((z + 1) * xCount));
				unsigned int p3 = (p3 = (x + 1) + ((z) * xCount));
				inMesh->triangles.emplace_back(p1, p2, p3);

				inMesh->vertices[p1].Normal = CalcNormal(inMesh->vertices[p1], inMesh->vertices[p2], inMesh->vertices[p3]);

				p1 = (p1 = x + ((z + 1) * xCount));
				p2 = (p2 = (x + 1) + ((z + 1) * xCount));
				p3 = (p3 = (x + 1) + ((z)*xCount));

				inMesh->triangles.emplace_back(p1, p2, p3);

				inMesh->vertices[p1].Normal = CalcNormal(inMesh->vertices[p1], inMesh->vertices[p2], inMesh->vertices[p3]);

			}
		}
		else
		{
			for (int z = 0; z < zCount - 1; z++)
			{
				unsigned int p1 = (p1 = (x + (z * xCount)));
				unsigned int p2 = (p2 = x + ((z + 1) * xCount));
				unsigned int p3 = (p3 = (x + 1) + (z + 1) * xCount);
				inMesh->triangles.emplace_back(p1, p2, p3);


				inMesh->vertices[p1].Normal = CalcNormal(inMesh->vertices[p1], inMesh->vertices[p2], inMesh->vertices[p3]);

				p1 = (p1 = x + (z * xCount));
				p2 = (p2 = (x + 1) + ((z + 1) * xCount));
				p3 = (p3 = (x + 1) + ((z)*xCount));

				inMesh->triangles.emplace_back(p1, p2, p3);


				inMesh->vertices[p1].Normal = CalcNormal(inMesh->vertices[p1], inMesh->vertices[p2], inMesh->vertices[p3]);
			

			}
		}
	}

	// Normalize all vertex Normals
	for (auto& Vertex : inMesh->vertices)
	{
		Vertex.Normal = glm::normalize(Vertex.Normal);
	}

	inMesh->meshType = Mesh::mt_Triangle;
	std::cout << "Plane created with : " << inMesh->vertices.size() << " vertices and : " << inMesh->triangles.size() << " triangles." << std::endl;

}

glm::vec3 MeshGenerator::Interpolate(glm::vec3 from, glm::vec3 to, float percent)
{
	glm::vec3 difference = to - from;
	return from + (difference * percent);
}

void MeshGenerator::GenerateCurve(Mesh* inMesh, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float step)
{
	
	for (float i = 0; i < 1; i += step)
	{
		// The Green Line
		glm::vec3 Va = Interpolate(p1, p2, i);
		glm::vec3 Vb = Interpolate(p2, p3, i);

		// The Black Dot
		glm::vec3 x = Interpolate(Va, Vb, i);

		inMesh->vertices.emplace_back(x, x, x);

	}
	inMesh->meshType = Mesh::mt_Line;
	std::cout << "Line generated with: " << inMesh->vertices.size() << " vertices\n";
}
