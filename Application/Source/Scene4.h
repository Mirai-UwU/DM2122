#pragma once
#ifndef SCENE_4_H
#define SCENE_4_H

#include "Scene.h"
#include "Camera.h"

class Scene4 : public Scene
{
	float rotateAngle;
	float translateX;
	float translateA;
	float translateB;
	float translateC;
	float translateD;
	float scaleAll;
	int rotateDirection;
	Camera camera;



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
		GEO_TRIANGLE_10,
		GEO_TRIANGLE_11,
		GEO_TRIANGLE_12,
		NUM_GEOMETRY,
	};

public:
	Scene4();
	~Scene4();

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