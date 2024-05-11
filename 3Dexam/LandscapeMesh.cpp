#include "LandscapeMesh.h"

int LandscapeMesh::GetTriangle(glm::vec3 point)
{
	float xPos = point.x;
	float zPos = point.z;

	int indexX = xPos / StepSize;
	int indexZ = zPos / StepSize;

	int index = indexX + (indexZ * xCount);
	//std::cout << indexX << " " << indexZ << std::endl;

	//std::cout << "Index: " << index << std::endl;



	return index;
}
