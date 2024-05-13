#include "Pickups.h"

void Pickups::AABB_CollisionResponse()
{
	hidden = true;
	AABB_Enabled = false;
}
