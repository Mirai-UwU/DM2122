#ifndef LIGHT_H
#define LIGHT_H

#include "Mesh.h"
#include "Vertex.h"

struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;

	Light()  
	{
		power = 10.f;
		kC = 1.f;
		kL = 0.01f;
		kQ = 0.001f;
	}
};
#endif
