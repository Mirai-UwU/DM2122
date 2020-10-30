#include "Scene2.h"
#include "GL\glew.h"

#include "shader.hpp"


Scene2::Scene2()
{
}

Scene2::~Scene2()
{
}

void Scene2::Init()
{
	// Init VBO here
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	
	//Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	//An array of 3 vectors which represents 3 vertices 
	static const GLfloat vertex_buffer_data[] =
	{
		1.0f,0.0f,0.0f,
		0.707f,0.707f,0.0f,
		0.0f,1.0f,0.0f,
		-0.707f,0.707f,0.0f,
		-1.0f,0.0f,0.0f,
		-0.707f,-0.707f,0.0f,
		0.0f,-1.0f,0.0f,
		0.707f,-0.707f,0.0f,
		1.0f,0.0f,0.0f,
		


		//part 2 answer
		//0.0f,0.4f,0.0f,
		//0.1f,0.2f,0.0f,
		//-0.1f,0.2f,0.0f,
		//0.1f,0.2f,0.0f,
		//0.1f,-0.1f,0.0f,
		//0.3f,0.0f,0.0f,		
		//0.1f,-0.1f,0.0f,
		//0.2f,-0.3f,0.0f,
		//0.0f,-0.2f,0.0f,
		//0.0f,-0.2f,0.0f,
		//-0.2f,-0.3f,0.0f,
		//-0.1f,-0.1f,0.0f,
		//-0.1f,-0.1f,0.0f,
		//-0.1f,0.2f,0.0f,
		//-0.3f,0.0f,0.0f,



		

	/*	part 3 answer
		-0.8f,0.2f,0.0f,
		-0.8f,0.0f,0.0f,
		0.8f,0.2f,0.0f,

		0.8f,0.0f,0.0f,
		0.8f,0.2f,0.0f,
		-0.8f,0.0f,0.0f,

		-0.8f,0.2f,0.0f,
		-0.2f,0.04f,0.0f,
		0.2f,0.4f,0.0f,

		0.2f,0.4f,0.0f,
		0.8f,0.2f,0.0f,
		-0.8f,0.2f,0.0f

		-0.8f,0.0f,0.0f,
		-0.2f,-0.4f,0.0f,
		0.8f,0.0f,0.0f,

		-0.2f,-0.4f,0.0f,
		0.2f,0.4f,0.0f,
		0.8f,0.0f,0.0f,*/


	};


	//Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	// Transfer vertices to OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data[]=
	{
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,



		//part 2 color
		//1.0f, 0.0f, 0.0f,
		//1.0f, 0.0f, 0.0f,
		//1.0f, 0.0f, 0.0f,
		//0.5f, 0.3f, 0.1f,
		//0.7f, 0.8f, 0.9f,
		//0.4f, 0.7f, 0.5f,
		//0.5f, 0.7f, 0.3f,
		//1.0f, 0.6f, 0.7f,
		//0.6f, 0.5f, 0.3f,
		//0.5f, 0.7f, 0.3f,
		//0.6f, 0.4f, 0.6f,
		//0.2f, 0.3f, 0.5f,
		//0.4f, 0.3f, 0.2f,
		//0.7f, 0.5f, 0.6f,
		//0.5f, 0.3f, 0.9f,

		/*part 3 colour
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.5f, 0.3f, 0.1f,
		0.7f, 0.8f, 0.9f,
		0.4f, 0.7f, 0.5f,
		0.5f, 0.7f, 0.3f,
		1.0f, 0.6f, 0.7f,
		0.7f, 0.8f, 0.9f,
		0.4f, 0.7f, 0.5f,
		0.5f, 0.7f, 0.3f,
		1.0f, 0.6f, 0.7f,
		0.7f, 0.8f, 0.9f,
		0.4f, 0.7f, 0.5f,
		0.5f, 0.3f, 0.4f,
		1.0f, 0.3f, 0.6f,
		0.6f, 0.4f, 0.3f,
		0.2f, 0.4f, 0.7f,*/
		
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	//2nd triangle
	static const GLfloat vertex_buffer_data2[] =
	{
		1.0f,1.0f,0.7f, //vertex 0 of triangle 
		1.0f,0.0f,0.5f, //vertex 1 of triangle
		-1.0f,-1.0f,0.3f, //vertex 2 of triangle

	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data2[] =
	{
		0.3f, 0.6f, 0.4f, //color of vertex 0
		0.2f, 0.9f, 0.3f, //color of vertex 1
		0.7f, 0.2f, 0.8f, //color if vertex 2

	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2), color_buffer_data2, GL_STATIC_DRAW);

	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//SimpleVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	// Use our shader
	glUseProgram(m_programID);


	//Enable depth test
	glEnable(GL_DEPTH_TEST);
}

void Scene2::Update(double dt)
{
}

void Scene2::Render()
{
	// Render VBO here
	// Clear color & depth buffer everty frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	glEnableVertexAttribArray(1); //2nd attribute buffer: colors

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
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 30); // Draw triangle ,Strarting from vertex 0; 3 vertices = 1 triangle
	


	//answer for part 2
	//glDrawArrays(GL_TRIANGLES, 0, 15); 

	//answer for part 3
	//glDrawArrays(GL_TRIANGLES, 0, 18); 


	/*Render second triangle
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(0, 3,  GL_FLOAT,  GL_FALSE,  0,  0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3); 

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1); */
}

void Scene2::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
