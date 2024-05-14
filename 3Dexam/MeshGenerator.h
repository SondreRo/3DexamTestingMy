#pragma once
#include "Mesh.h"
#include "LandscapeMesh.h"
class MeshGenerator
{
	static float Function(float x, float z);
	static glm::vec3 CalcNormal(Vertex& p1, Vertex& p2, Vertex& p3);
public:

	static void GenerateTriangle(Mesh* inMesh, glm::vec3 Size);

	static void GenerateSquare(Mesh* inMesh, glm::vec3 Size);

	static void GenerateBox(Mesh* inMesh, glm::vec3 Size);

	static void GenerateLandscape(LandscapeMesh* inMesh, int xCount, int zCount, float stepSize);

	static glm::vec3 Interpolate(glm::vec3 from, glm::vec3 to, float percent);
	
	static void GenerateCurve(Mesh* inMesh, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float step);
};

