#include "Npc.h"

Npc::Npc()
{
}

void Npc::Tick(float deltaTime)
{
	Mesh::Tick(deltaTime);

	if (pointsToFollow.size() <= 0) return;

	TimeSinceLastChange += deltaTime;

	if (TimeSinceLastChange >= JumpFrequency)
	{
		TimeSinceLastChange = 0;

		if (CurrentIndex >= pointsToFollow.size() - 1)
		{
			GoingForward = false;
		}
		if (CurrentIndex <= 0 + 1)
		{
			GoingForward = true;
		}

		if (GoingForward)
		{
			CurrentIndex += 1;
		}
		else
		{
			CurrentIndex -= 1;
		}


		//if (CurrentIndex >= pointsToFollow.size()) return;


		transform.SetLocation(pointsToFollow[CurrentIndex].Position + glm::vec3(0, HeightOfsett, 0));



	}
}
