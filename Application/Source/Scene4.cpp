#include "Scene4.h"
#include "GL\glew.h"
#include "Application.h"

#include "shader.hpp"
#include <Mtx44.h>
#include "MeshBuilder.h"
#include "Mesh.h"


Scene4::Scene4()
{
}

Scene4::~Scene4()
{
}

void Scene4::Init()
{
	rotateAngle = 0;
	translateX = 8;
	scaleAll = 8;

	glEnable(GL_CULL_FACE);
	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", 1, 1);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1, 1);
	

	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	// Use our shader
	glUseProgram(m_programID);

	//Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	// Init VBO here
	// Set background color to dark blue
	glClearColor(0.2f, 0.5f, 0.4f, 0.0f);

	

	//An array of 3 vectors which represents 3 vertices 
	static const GLfloat vertex_buffer_data[] =
	{

		0.5f,0.5f,0.0f,
		-0.5f,0.5f,0.0f,
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,


	};

	static const GLfloat color_buffer_data[] =
	{
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,



	};


	static const GLuint index_buffer_data[] =
	{

		0,1,2,0,2,3,
	};

	//Set the current active buffer
	// Transfer vertices to OPENGL


	

	//Enable depth test
	glEnable(GL_DEPTH_TEST);
}

void Scene4::Update(double dt)
{
	camera.Update(dt);

	rotateAngle -= (float)(1 * dt);
	translateX -= (float)(5 * dt);
	translateA -= (float)(3 * dt);
	translateB -= (float)(3 * dt);
	translateC -= (float)(3 * dt);
	translateD -= (float)(3 * dt);
	scaleAll -= (float)(2 * dt);


	if ((rotateDirection != -1) && (rotateAngle < 1))
	{
		rotateDirection = 1;
	}
	else if ((rotateDirection == -1) && (rotateAngle <= -1))
	{
		rotateDirection = 1;
	}
	else
	{
		rotateDirection = -1;
	}

	rotateAngle += (float)(rotateDirection * 10 * dt);

	if (Application::IsKeyPressed(VK_SPACE))
	{
		if (translateX >= -100)
		{
			translateA = 0;
			if (translateA >= 40)
			{
				translateA = 0;
			}
			translateB = -10;
			if (translateB >= 40)
			{
				translateB = 0;
			}
			translateC = -30;
			if (translateC >= 40)
			{
				translateC = 0;
			}
			translateD = 30;
			if (translateD >= 40)
			{
				translateD = 0;
			}
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

	if (Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glEnable(GL_FILL);
	if (Application::IsKeyPressed('4'))
		glDisable(GL_LINE);

}

void Scene4::Render()
{
	model.SetToIdentity();
	Mtx44 MVP = projection * view * model;
	glUniformMatrix4fv(m_parameter[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_AXES]->Render();
	meshList[GEO_QUAD]->Render();
	meshList[GEO_CUBE]->Render();

}

void Scene4::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
