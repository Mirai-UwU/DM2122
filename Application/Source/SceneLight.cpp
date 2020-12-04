#include "SceneLight.h"
#include "GL\glew.h"
#include "Application.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "Mesh.h"
#include <vector>
#include "Utility.h"


SceneLight::SceneLight()
{
}

SceneLight::~SceneLight()
{
}

void SceneLight::Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	rotateAngle = 0;
	translateX = 8;
	scaleAll = 8;


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	

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
	


	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	glUseProgram(m_programID);

	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	// Make sure you pass uniform parameters after glUseProgram()
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1.f, 0.0f, 0.0f), 1.0f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0.5f, 0.2f, 0.0f), 1);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sphere", Color(0.5, 0.5, 0.5), 10, 10, 10);
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;
	meshList[GEO_SPHERE1] = MeshBuilder::GenerateSphere("Sphere1", Color(0.0, 0.0, 1.0), 10, 10, 10);
	meshList[GEO_SPHERE1]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE1]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE1]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE1]->material.kShininess = 1.f;
	meshList[GEO_SPHERE2] = MeshBuilder::GenerateSphere("Sphere2", Color(1.0, 0.0, 1.0), 10, 10, 10);
	meshList[GEO_SPHERE2]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE2]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE2]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE2]->material.kShininess = 1.f;
	meshList[GEO_SPHERE3] = MeshBuilder::GenerateSphere("Sphere3", Color(0.0, 0.5, 1.0), 10, 10, 10);
	meshList[GEO_SPHERE3]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE3]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE3]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE3]->material.kShininess = 1.f;
	meshList[GEO_SPHERE4] = MeshBuilder::GenerateSphere("Sphere4", Color(1.0, 0.0, 0.0), 10, 10, 10);
	meshList[GEO_SPHERE4]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE4]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE4]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE4]->material.kShininess = 1.f;
	meshList[GEO_SPHERE5] = MeshBuilder::GenerateSphere("Sphere5", Color(0.0, 1.0, 0.0), 10, 10, 10);
	meshList[GEO_SPHERE5]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE5]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE5]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE5]->material.kShininess = 1.f;
	meshList[GEO_SPHERE6] = MeshBuilder::GenerateSphere("Sphere6", Color(1.0, 1.0, 0.0), 10, 10, 10);
	meshList[GEO_SPHERE6]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE6]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE6]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE6]->material.kShininess = 1.f;
	meshList[GEO_SPHERE7] = MeshBuilder::GenerateSphere("Sphere7", Color(0.1, 0.0, 0.0), 10, 10, 10);
	meshList[GEO_SPHERE7]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE7]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE7]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE7]->material.kShininess = 1.f;
	meshList[GEO_SPHERE8] = MeshBuilder::GenerateSphere("Sphere8", Color(0.5, 0.5, 0.5), 10, 10, 10);
	meshList[GEO_SPHERE8]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE8]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE8]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE8]->material.kShininess = 1.f;
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("Lightball", Color(1, 1, 1), 10, 10, 10);


	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);
}

void SceneLight::Update(double dt)
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

	static const float LSPEED = 30.f;
	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);


}

void SceneLight::Render()
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

	RenderMesh(meshList[GEO_AXES], false);
	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	modelStack.Scale(0.2, 0.2, 0.2);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -10, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(100, 100, 100);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

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
		////2nd object
		//modelStack.PushMatrix();
		//modelStack.Translate(-2, 0, 0);
		//MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
		//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		//meshList[GEO_CUBE]->Render();
		//modelStack.PopMatrix();
	
	//Solar System
	/*modelStack.PushMatrix();*/

	//Row 1 1st planet 
	modelStack.PushMatrix();
	modelStack.Rotate(0, 1, 3, 3);
	modelStack.Translate(-10, 0, 0);
	modelStack.Scale(0.5, 0.5, 0.5);
	RenderMesh(meshList[GEO_SPHERE8], true);
	modelStack.PopMatrix();


	//Row 1 2nd planet (MAIN PLANET IS THIS)
	modelStack.PushMatrix();
	modelStack.Rotate(rotateAngle, 1, 3, 3); //revolution
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(rotateAngle, 1, 3, 3); //rotation
	modelStack.Scale(0.5, 0.5, 0.5);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	//Row 1 3rd planet
	modelStack.PushMatrix();
	modelStack.Rotate(0, 1, 3, 3); 
	modelStack.Translate(10, 0, 0);
	modelStack.Scale(0.5, 0.5, 0.5);
	RenderMesh(meshList[GEO_SPHERE1], true);
	modelStack.PopMatrix();

	//Row 2 1st planet
	modelStack.PushMatrix();
	modelStack.Rotate(0, 1, 3, 3);
	modelStack.Translate(-10, 0, 10);
	modelStack.Scale(0.5, 0.5, 0.5);
	RenderMesh(meshList[GEO_SPHERE4], true);
	modelStack.PopMatrix();

	//Rowa 2 2nd planet
	modelStack.PushMatrix();
	modelStack.Rotate(0, 1, 3, 3);
	modelStack.Translate(0, 0, 10);
	modelStack.Scale(0.5, 0.5, 0.5);
	RenderMesh(meshList[GEO_SPHERE3], true);
	modelStack.PopMatrix();

	//Row 2 3rd planet
	modelStack.PushMatrix();
	modelStack.Rotate(0, 1, 3, 3);
	modelStack.Translate(10, 0, 10);
	modelStack.Scale(0.5, 0.5, 0.5);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();


	//Row 3 1st planet
	modelStack.PushMatrix();
	modelStack.Rotate(0, 1, 3, 3);
	modelStack.Translate(-10, 0, 20);
	modelStack.Scale(0.5, 0.5, 0.5);
	RenderMesh(meshList[GEO_SPHERE5], true);
	modelStack.PopMatrix();

	//Row 3 2nd planet
	modelStack.PushMatrix();
	modelStack.Rotate(0, 1, 3, 3);
	modelStack.Translate(0, 0, 20);
	modelStack.Scale(0.5, 0.5, 0.5);
	RenderMesh(meshList[GEO_SPHERE6], true);
	modelStack.PopMatrix();

	//Row 3 3rd planet
	modelStack.PushMatrix();
	modelStack.Rotate(0, 1, 3, 3);
	modelStack.Translate(10, 0, 20);
	modelStack.Scale(0.5, 0.5, 0.5);
	RenderMesh(meshList[GEO_SPHERE7], true);
	modelStack.PopMatrix();

	/*modelStack.PushMatrix();
	modelStack.Rotate(30, 1, 0, 0);
	modelStack.Scale(10, 10, 10);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SPHERE]->Render();
	modelStack.PopMatrix();*/

	

}

void SceneLight::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	mesh->Render();
}





void SceneLight::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
