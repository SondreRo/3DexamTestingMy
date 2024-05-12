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
	virtual ~Mesh() = default;

	enum MeshType
	{
		mt_Triangle,
		mt_Line,
		mt_Dot
	};

	Transform transform;

	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;

	void Bind();
	void Draw(glm::mat4 CamMat);
	virtual void Tick(float deltaTime);

	Shader* shader;


	MeshType meshType = mt_Triangle;
	void Cleanup();
};

