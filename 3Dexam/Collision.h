#pragma once
#include <string>
#include <vector>

#include "glm/glm.hpp"
class Collision
{

};

class SphereCollider
{
public:
	static bool CheckCollision(glm::vec3 p1, float r1, glm::vec3 p2, float r2);
};

class AABBCollider
{
	
public:
	glm::vec3 Position;
	glm::vec3 Size;
	enum CollisionDirection
	{
		North,
		South,
		West,
		East,
		Up,
		Down
	};
	static bool CheckCollision(glm::vec3 p1, glm::vec3 s1, glm::vec3 p2, glm::vec3 s2);
	static bool CheckDistance(float target, std::vector<float> other);
};