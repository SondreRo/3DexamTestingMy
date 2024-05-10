#pragma once
#include "Mesh.h"

class LandscapeMesh : public Mesh
{

public:
	int xCount = 0;
	int zCount = 0;
	float StepSize = 0;

	int GetTriangle(glm::vec3 point);
};

