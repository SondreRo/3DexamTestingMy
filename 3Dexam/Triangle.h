#pragma once
struct Triangle
{
	Triangle(unsigned int inP1, unsigned int inP2, unsigned int inP3)
	{
		P1 = inP1;
		P2 = inP2;
		P3 = inP3;
	}
	unsigned int P1 = 0;
	unsigned int P2 = 0;
	unsigned int P3 = 0;
};

