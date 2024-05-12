#pragma once
#include "Mesh.h"
class Npc : public Mesh
{
	float TimeSinceLastChange = 0.f;
	int CurrentIndex = 0;

	bool GoingForward = true;
public:
	Npc();
	float JumpFrequency = 1.0f/60.0f;
	void Tick(float deltaTime) override;
	std::vector<Vertex> pointsToFollow;

	float HeightOfsett = 0;
};

