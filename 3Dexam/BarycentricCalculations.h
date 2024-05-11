#pragma once
#include "LandscapeMesh.h"
#include "Mesh.h"

class BarycentricCalculations
{

	static void Switch(glm::vec3& inVec);
public:

	static bool Calculate(LandscapeMesh* inMesh, glm::vec3 target, glm::vec3& FoundCoords);
};

