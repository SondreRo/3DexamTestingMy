#pragma once
#include <ostream>
#include <vector>

#include "CollisionCalculation.h"
#include "Transform.h"
#include "Vertex.h"
#include "Triangle.h"

class Shader;

class Mesh : public AABBCollisionInterface
{
	unsigned int VBO{ 0 }, VAO{ 0 }, EBO { 0 };


	
public:
	virtual ~Mesh();

	friend std::ostream& operator<<(std::ostream& os, const Mesh& obj)
	{
		return os
			<< "vertices: " << obj.vertices.size()
			<< " triangles: " << obj.triangles.size();
	}

	enum MeshType
	{
		mt_Triangle,
		mt_Line,
		mt_Dot
	};

	virtual void AABB_CollisionResponse() override;

	Transform transform;

	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;

	void Bind();
	void Draw(glm::mat4 CamMat, glm::vec3 CamPos);
	virtual void Tick(float deltaTime);

	Shader* shader;

	bool hidden = false;

	MeshType meshType = mt_Triangle;
	void Cleanup();
};

