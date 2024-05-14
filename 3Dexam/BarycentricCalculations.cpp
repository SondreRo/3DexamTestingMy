#include "BarycentricCalculations.h"

bool BarycentricCalculations::Calculate(LandscapeMesh* inMesh, glm::vec3 target, glm::vec3& FoundCoords)
{

	glm::vec3 AdTarget = glm::vec3(target.x, target.z, 0);
	for (auto triangle : inMesh->triangles)
	{
		glm::vec3 P = glm::vec3(inMesh->vertices[triangle.P1].Position.x, inMesh->vertices[triangle.P1].Position.z, 0.f);
		glm::vec3 Q = glm::vec3(inMesh->vertices[triangle.P2].Position.x, inMesh->vertices[triangle.P2].Position.z, 0.f);
		glm::vec3 R = glm::vec3(inMesh->vertices[triangle.P3].Position.x, inMesh->vertices[triangle.P3].Position.z, 0.f);

		float Ar = glm::length(glm::cross(Q - P, R - P));

		float U = (glm::cross(Q - AdTarget, R - AdTarget).z) / Ar;
		float V = (glm::cross(R - AdTarget, P - AdTarget).z) / Ar;
		float W = (glm::cross(P - AdTarget, Q - AdTarget).z) / Ar;

		if (U >= 0 && V >= 0 && W >= 0)
		{
			//std::cout << triangle.P1 << std::endl;

			FoundCoords = U * inMesh->vertices[triangle.P1].Position + V * inMesh->vertices[triangle.P2].Position + W * inMesh->vertices[triangle.P3].Position;
			return true;
		}
	}

	return false;
}
