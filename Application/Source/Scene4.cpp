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
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(0.5f,0.8f,0.4f), 1.0f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1);
	

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


	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));
	

	//Enable depth test
	glEnable(GL_DEPTH_TEST);
}

void Scene4::Update(double dt)
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

void Scene4::Render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToLookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);
	// projection.SetToOrtho(-10, 10, -10, 10, -10, 10); //Our world is a cube defined by these boundaries

	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f); //FOV, Aspect Ratio, Near plane, Far plane

	// triangle 1
	scale.SetToScale(2, 2, 2);
	rotate.SetToRotation(rotateAngle, 0, 1, 0);
	translate.SetToTranslation(0, 0, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
	meshList[GEO_QUAD]->Render();

}

void Scene4::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
