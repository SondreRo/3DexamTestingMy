#pragma once
#include <vector>

#include "Shader.h"
#include "Transform.h"
#include "Vertex.h"
#include "Triangle.h"

class Mesh
{
	unsigned int VBO{ 0 }, VAO{ 0 }, EBO { 0 };


public:

	Transform transform;

	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;

	void Bind();
	void Draw(Shader shader);

	void Cleanup();
};

