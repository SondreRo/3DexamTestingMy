#include "BarycentricCalculations.h"

void BarycentricCalculations::Switch(glm::vec3& inVec)
{
	glm::vec3 TempVec = inVec;

	inVec.x = TempVec.x;
	inVec.y = TempVec.z;
	inVec.z = TempVec.y;
}

bool BarycentricCalculations::Calculate(LandscapeMesh* inMesh, glm::vec3 target, glm::vec3& FoundCoords)
{
	//unsigned int temp = inMesh->GetTriangle(target);
	//
	//std::cout << temp << "    " << inMesh->triangles.size() <<  std::endl;
	//if (temp < 0 || temp > inMesh->triangles.size())
	//	return glm::vec3(0);

	//Triangle tri = inMesh->triangles[temp];
	//unsigned int indexA = tri.P1;
	//unsigned int indexB = tri.P2;
	//unsigned int indexC = tri.P3;

	//float height = 0;
	//glm::vec3 AdTarget = glm::vec3(target.x, target.z, 0);
	//glm::vec3 NewCoords;

	//glm::vec3 P = glm::vec3(inMesh->vertices[indexA].Position.x, inMesh->vertices[indexA].Position.z, 0.f);
	//glm::vec3 Q = glm::vec3(inMesh->vertices[indexB].Position.x, inMesh->vertices[indexB].Position.z, 0.f);
	//glm::vec3 R = glm::vec3(inMesh->vertices[indexC].Position.x, inMesh->vertices[indexC].Position.z, 0.f);

	//float Ar = glm::length(glm::cross(Q - P, R - P));

	//float U = (glm::cross(Q - AdTarget, R - AdTarget).z) / Ar;
	//float V = (glm::cross(R - AdTarget, P - AdTarget).z) / Ar;
	//float W = (glm::cross(P - AdTarget, Q - AdTarget).z) / Ar;

	//if (U >= 0 && V >= 0 && W >= 0)
	//{
	//	//std::cout << triangle.P1 << std::endl;
	//	return U * inMesh->vertices[indexA].Position + V * inMesh->vertices[indexB].Position + W * inMesh->vertices[indexC].Position;
	//}



	float height = 0;
	glm::vec3 AdTarget = glm::vec3(target.x, target.z, 0);
	glm::vec3 NewCoords;
	for (auto triangle : inMesh->triangles)
	{
		glm::vec3 P = glm::vec3(inMesh->vertices[triangle.P1].Position.x, inMesh->vertices[triangle.P1].Position.z, 0.f);
		glm::vec3 Q = glm::vec3(inMesh->vertices[triangle.P2].Position.x, inMesh->vertices[triangle.P2].Position.z, 0.f);
		glm::vec3 R = glm::vec3(inMesh->vertices[triangle.P3].Position.x, inMesh->vertices[triangle.P3].Position.z, 0.f);

		//glm::vec4 Pm = glm::vec4(P, 1.f);
		//glm::vec4 Qm = glm::vec4(Q, 1.f);
		//glm::vec4 Rm = glm::vec4(R, 1.f);
		//P = glm::vec3(inMesh->transform.GetMatrix() * Pm);
		//Q = glm::vec3(inMesh->transform.GetMatrix() * Qm);
		//R = glm::vec3(inMesh->transform.GetMatrix() * Rm);

		//P = glm::vec3(Pm);
		//Q = glm::vec3(Qm);
		//R = glm::vec3(Rm);

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
