#pragma once
#include <cmath>
#include <iostream>
#include <glm/vec3.hpp>

class AABBCollisionInterface
{
public:
	bool AABB_Enabled = false;
	glm::vec3 AABB_Position = glm::vec3(0);
	glm::vec3 AABB_Size = glm::vec3(0);

	virtual void AABB_CollisionResponse()
	{
		
	}
};

class CollisionCalculation
{
public:

	static bool AABBCheck(AABBCollisionInterface* AABB1, AABBCollisionInterface* AABB2)
	{
		glm::vec3 p1 = AABB1->AABB_Position;
		glm::vec3 p2 = AABB2->AABB_Position;
							
		glm::vec3 s1 = AABB1->AABB_Size;
		glm::vec3 s2 = AABB1->AABB_Size;

		// collision x-axis?
		bool collisionX = p1.x + s1.x >= p2.x &&
			p2.x + s2.x >= p1.x;

		// collision y-axis?
		bool collisionY = p1.y + s1.y >= p2.y &&
			p2.y + s2.y >= p1.y;

		// collision y-axis?
		bool collisionZ = p1.z + s1.z >= p2.z &&
			p2.z + s2.z >= p1.z;




		float xDist = abs((p1.x + s1.x) - (p2.x - s1.x)); // WEST
		//float xDist2 = abs((p1.x - s1.x) - (p2.x + s1.x)); // EAST

		float yDist = abs((p1.y + s1.y) - (p2.y - s1.y)); // Up
		//float yDist2 = abs((p1.y - s1.y) - (p2.y + s1.y)); // Down

		float zDist = abs((p1.z + s1.z) - (p2.z - s1.z)); // North
		//float zDist2 = abs((p1.z - s1.z) - (p2.z + s1.z)); // South

		

		if (collisionX && collisionY && collisionZ)
		{
			//std::cout << "X: " << xDist << " Y: " << yDist << " Z: " << zDist << std::endl;
			AABB1->AABB_CollisionResponse();
			AABB2->AABB_CollisionResponse();
			return true;
		}

		return false;
	}
};