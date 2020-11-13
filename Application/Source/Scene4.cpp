#include "Scene4.h"
#include "GL\glew.h"
#include "Application.h"

#include "shader.hpp"
#include <Mtx44.h>


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

	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	// Use our shader
	glUseProgram(m_programID);

	//Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	// Init VBO here
	// Set background color to dark blue
	glClearColor(0.2f, 0.5f, 0.4f, 0.0f);

	//Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	//An array of 3 vectors which represents 3 vertices 
	static const GLfloat vertex_buffer_data[] =
	{

		0.0f,0.2f,0.0f,
		0.1f,0.0f,0.0f,
		-0.1f,0.0f,0.0f,


	};


	//Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	// Transfer vertices to OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data[] =
	{
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,



	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	

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
	// Render VBO here
	// Clear color & depth buffer everty frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	glEnableVertexAttribArray(1); //2nd attribute buffer: colors

	//Creating new Matrix
	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;


	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity();
	view.SetToLookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z,camera.up.x,camera.up.y,camera.up.z);
	//projection.SetToOrtho(-40, +40, -40, +40, -40, +40);
	projection.SetToPerspective(45.f, 4.f / 3, 0.1f, 1000.f);



	//Render triangle
	scale.SetToScale(2, 2, 2);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-40, -50, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 30);;



	//Stop displaying
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Scene4::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
