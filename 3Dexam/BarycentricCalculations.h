#pragma once
#include "LandscapeMesh.h"
#include "Mesh.h"

class BarycentricCalculations
{

	static void Switch(glm::vec3& inVec);
public:

	static glm::vec3 Calculate(LandscapeMesh* inMesh, glm::vec3 target);
};

