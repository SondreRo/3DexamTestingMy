#pragma once
#include "CollisionCalculation.h"
#include "Mesh.h"
class Pickups : public Mesh
{
public:
	void AABB_CollisionResponse() override;
};

