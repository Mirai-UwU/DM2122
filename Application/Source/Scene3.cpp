#include "Scene3.h"
#include "GL\glew.h"
#include "Application.h"

#include "shader.hpp"
#include <Mtx44.h>


Scene3::Scene3()
{
}

Scene3::~Scene3()
{
}

void Scene3::Init()
{
	rotateAngle = 0;
	translateX = 8;
	scaleAll = 8;

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

	//2nd object
	static const GLfloat vertex_buffer_data2[] =
	{
		-0.6f,0.77f,0.0f,  
		-0.42f,0.77f,0.0f, 
		-0.58f,0.68f,0.0f, 
		-0.64f,1.0f,0.0f,
		-0.68f,0.77f,0.0f,
		-0.60f,0.77f,0.0f,
		-0.68f,0.77f,0.0f,
		-0.70f,0.68f,0.0f,
		-0.86f,0.77f,0.0f,
		-0.64f,0.63f,0.0f,
		-0.70f,0.68f,0.0f,
		-0.82f,0.43f,0.0f,
		-0.64f,0.63f,0.0f,
		-0.58f,0.68f,0.0f,
		-0.51f,0.43f,0.0f,

	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data2[] =
	{
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,


	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2), color_buffer_data2, GL_STATIC_DRAW);

	//3rd object
	static const GLfloat vertex_buffer_data3[] =
	{
		-0.6f,0.77f,0.0f,
		-0.42f,0.77f,0.0f,
		-0.58f,0.68f,0.0f,
		-0.64f,1.0f,0.0f,
		-0.68f,0.77f,0.0f,
		-0.60f,0.77f,0.0f,
		-0.68f,0.77f,0.0f,
		-0.70f,0.68f,0.0f,
		-0.86f,0.77f,0.0f,
		-0.64f,0.63f,0.0f,
		-0.70f,0.68f,0.0f,
		-0.82f,0.43f,0.0f,
		-0.64f,0.63f,0.0f,
		-0.58f,0.68f,0.0f,
		-0.51f,0.43f,0.0f,

	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data3), vertex_buffer_data3, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data3[] =
	{
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,


	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data3), color_buffer_data3, GL_STATIC_DRAW);

	//4th object
	static const GLfloat vertex_buffer_data4[] =
	{
		-0.6f,0.77f,0.0f,
		-0.42f,0.77f,0.0f,
		-0.58f,0.68f,0.0f,
		-0.64f,1.0f,0.0f,
		-0.68f,0.77f,0.0f,
		-0.60f,0.77f,0.0f,
		-0.68f,0.77f,0.0f,
		-0.70f,0.68f,0.0f,
		-0.86f,0.77f,0.0f,
		-0.64f,0.63f,0.0f,
		-0.70f,0.68f,0.0f,
		-0.82f,0.43f,0.0f,
		-0.64f,0.63f,0.0f,
		-0.58f,0.68f,0.0f,
		-0.51f,0.43f,0.0f,

	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data4), vertex_buffer_data4, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data4[] =
	{
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,


	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data4), color_buffer_data4, GL_STATIC_DRAW);

	//5th object
	static const GLfloat vertex_buffer_data5[] =
	{
		-0.6f,0.77f,0.0f,
		-0.42f,0.77f,0.0f,
		-0.58f,0.68f,0.0f,
		-0.64f,1.0f,0.0f,
		-0.68f,0.77f,0.0f,
		-0.60f,0.77f,0.0f,
		-0.68f,0.77f,0.0f,
		-0.70f,0.68f,0.0f,
		-0.86f,0.77f,0.0f,
		-0.64f,0.63f,0.0f,
		-0.70f,0.68f,0.0f,
		-0.82f,0.43f,0.0f,
		-0.64f,0.63f,0.0f,
		-0.58f,0.68f,0.0f,
		-0.51f,0.43f,0.0f,

	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data5), vertex_buffer_data5, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data5[] =
	{
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,


	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data5), color_buffer_data5, GL_STATIC_DRAW);

	//6th object
	static const GLfloat vertex_buffer_data6[] =
	{
		0.0f,0.4f,0.0f,
		0.1f,0.2f,0.0f,
		-0.1f,0.2f,0.0f,

	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data6), vertex_buffer_data6, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data6[] =
	{
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,



	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data6), color_buffer_data6, GL_STATIC_DRAW);

	//7th object
	static const GLfloat vertex_buffer_data7[] =
	{
		0.0f,0.4f,0.0f,
		0.1f,0.2f,0.0f,
		-0.1f,0.2f,0.0f,

	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_7]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data7), vertex_buffer_data7, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data7[] =
	{
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,


	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_7]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data7), color_buffer_data7, GL_STATIC_DRAW);

	//8th object
	static const GLfloat vertex_buffer_data8[] =
	{
		0.0f,0.4f,0.0f,
		0.1f,0.2f,0.0f,
		-0.1f,0.2f,0.0f,

	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_8]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data8), vertex_buffer_data8, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data8[] =
	{
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,


	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_8]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data8), color_buffer_data8, GL_STATIC_DRAW);



	//Enable depth test
	glEnable(GL_DEPTH_TEST);
}

void Scene3::Update(double dt)
{
	rotateAngle -= (float)(10 * dt);
	translateX -= (float)(5 * dt);
	scaleAll -= (float)(2 * dt);

	if (Application::IsKeyPressed(VK_SPACE))
	{
		if (scaleAll >= -100)
		{
			scaleAll = 1;
		}

		if (rotateAngle >= -90)
		{
			rotateAngle = 1;
		}

		if (translateX >= -100)
		{
			translateX = 8;
		}

	}

}

void Scene3::Render()
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

	//OBJECT 1
	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity();
	projection.SetToOrtho(-8, +8, -8, +8, -8, +8);

	scale.SetToScale(18, 9, 18);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(3,0, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	//Render triangle
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(
		0,  //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
		3,  // size
		GL_FLOAT,  //type
		GL_FALSE,  //normalized?
		0,  //stride
		0   //array buffer offset
	);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 30); // Draw triangle ,Strarting from vertex 0; 3 vertices = 1 triangle


	//OBJECT 2
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(1, 0, 0, 1);
	translate.SetToTranslation(-translateX, 7, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 15);


	//3rd object
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(135, 0, 0, 1);
	translate.SetToTranslation(-translateX, 7, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 15);

	//4th object
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(135, 0, 0, 1);
	translate.SetToTranslation(-translateX, 8, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_4]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_4]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 15);

	//5th object
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(135, 0, 0, 1);
	translate.SetToTranslation(-translateX, 6, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_5]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_5]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 15);

	//6th object
	scale.SetToScale(8, 6, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-3, -2, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_6]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_6]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 15);

	//7th object
	scale.SetToScale(6, 6, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-3, -1, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_7]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_7]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 15);

	//8th object
	scale.SetToScale(10, 6, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-3, -3, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_8]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_8]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 15);



	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


}

void Scene3::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
