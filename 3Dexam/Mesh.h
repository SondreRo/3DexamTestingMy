#pragma once
#include <vector>

#include "Transform.h"
#include "Vertex.h"
#include "Triangle.h"

class Shader;

class Mesh
{
	unsigned int VBO{ 0 }, VAO{ 0 }, EBO { 0 };

	
public:

	Transform transform;

	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;

	void Bind();
	void Draw(glm::mat4 CamMat);
	virtual void Tick(float deltaTime);

	Shader* shader;

	void Cleanup();
};

