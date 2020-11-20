#include "Scene5.h"
#include "GL\glew.h"
#include "Application.h"

#include "shader.hpp"
#include <Mtx44.h>
#include "MeshBuilder.h"
#include "Mesh.h"
#include <vector>


Scene5::Scene5()
{
}

Scene5::~Scene5()
{
}

void Scene5::Init()
{
	rotateAngle = 0;
	translateX = 8;
	scaleAll = 8;

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);


	glEnable(GL_CULL_FACE);
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(0.5f,0.8f,0.4f), 1.0f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0.5f,0.2f,0.0f), 1);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sphere", Color(0.0f, 0.0f, 0.8f), 16, 24,1);
	

	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	// Use our shader
	glUseProgram(m_programID);

	//Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	// Init VBO here
	// Set background color to dark blue
	glClearColor(0.2f, 0.5f, 0.4f, 0.0f);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);


	camera.Init(Vector3(40, 30, 30), Vector3(0, 0, 0), Vector3(0, 1, 0));
	

	//Enable depth test
	glEnable(GL_DEPTH_TEST);
}

void Scene5::Update(double dt)
{
	camera.Update(dt);

	if (Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	rotateAngle -= (float)(1 * dt);
	translateX -= (float)(5 * dt);
	scaleAll -= (float)(2 * dt);

	if (Application::IsKeyPressed(VK_SPACE))
	{
		if (translateX >= -100)
		{
			translateX = 1;
		}
		
		if (scaleAll >= -100)
		{
			scaleAll = 1;
		}

		if (rotateAngle >= -180)
		{
			rotateAngle = 1;
		}

	}


}

void Scene5::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 MVP;
	viewStack.LoadIdentity(); //no need camera for now, set it at World's origin
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);
	modelStack.LoadIdentity();

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_AXES]->Render();

	//	//1st object
	//	modelStack.PushMatrix();
	//	modelStack.Translate(2, 0, 0);
	//	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	//	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//	meshList[GEO_CUBE]->Render();
	//	modelStack.PopMatrix();
	//
	//	//2nd object
	//	modelStack.PushMatrix();
	//	modelStack.Translate(-2, 0, 0);
	//	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	//	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//	meshList[GEO_CUBE]->Render();
	//	modelStack.PopMatrix();
	
	//Solar System
	modelStack.PushMatrix();

	//Planet 1
	modelStack.PushMatrix();
	modelStack.Rotate(rotateAngle, 1, 3, 3); //revolution
	modelStack.Translate(20, 0, 0);
	modelStack.Rotate(rotateAngle, 1, 3, 3); //rotation
	modelStack.Scale(3, 3, 3);
	modelStack.PopMatrix();

	modelStack.Rotate(30, 1, 0, 0);
	modelStack.Scale(10, 10, 10);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SPHERE]->Render();
	modelStack.PopMatrix();

}







void Scene5::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
