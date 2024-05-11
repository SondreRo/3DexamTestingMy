#include "Collision.h"

#include <iostream>

bool SphereCollider::CheckCollision(glm::vec3 p1, float r1, glm::vec3 p2, float r2)
{
	float TotalRadius = r1 + r2;
	float Difference = glm::length(p2 - p1);

	
	return (Difference < TotalRadius);
}

bool AABBCollider::CheckCollision(glm::vec3 p1, glm::vec3 s1, glm::vec3 p2, glm::vec3 s2)
{
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
	float xDist2 = abs((p1.x - s1.x) - (p2.x + s1.x)); // EAST

	float yDist = abs((p1.y + s1.y) - (p2.y - s1.y)); // Up
	float yDist2 = abs((p1.y - s1.y) - (p2.y + s1.y)); // Down

	float zDist = abs((p1.z + s1.z) - (p2.z - s1.z)); // North
	float zDist2 = abs((p1.z - s1.z) - (p2.z + s1.z)); // South


	

	CollisionDirection CD;

	if (collisionX && collisionY && collisionZ)
	{
		std::cout <<"X: " << xDist << " Y: " << yDist << " Z: " << zDist << std::endl;

		return true;
	}

	return false;
}

bool AABBCollider::CheckDistance(float target, std::vector<float> other)
{
	for (float length : other)
	{
		if (length == target) continue;


	}
}

