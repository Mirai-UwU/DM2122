#pragma once
#ifndef SCENE_3_H
#define SCENE_3_H

#include "Scene.h"

class Scene3 : public Scene
{
	float rotateAngle;
	float translateX;
	float translateA;
	float translateB;
	float translateC;
	float translateD;
	float scaleAll;
	int rotateDirection;



	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};

	unsigned m_parameters[U_TOTAL];


	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		GEO_TRIANGLE_2,
		GEO_TRIANGLE_3,
		GEO_TRIANGLE_4,
		GEO_TRIANGLE_5,
		GEO_TRIANGLE_6,
		GEO_TRIANGLE_7,
		GEO_TRIANGLE_8,
		GEO_TRIANGLE_9,
		NUM_GEOMETRY,
	};

public:
	Scene3();
	~Scene3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;
};




#endif