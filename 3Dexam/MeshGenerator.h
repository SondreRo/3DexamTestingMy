#pragma once
#include "Mesh.h"
#include "LandscapeMesh.h"
class MeshGenerator
{
	static float Function(float x, float z);
	static glm::vec3 CalcNormal(Vertex& p1, Vertex& p2, Vertex& p3);
public:

	static void GenerateBox(Mesh* inMesh, glm::vec3 Size);

	static void GenerateLandscape(LandscapeMesh* inMesh, int xCount, int zCount, float stepSize);
};

