#include "MeshBuilder.h"
#include "GL\glew.h"
#include <vector>
#include "Vertex.h"

Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{

}

Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, float lengthX, float lengthY)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	v.pos.Set(0.5f, 0.5f, 0.0f); v.color.Set(1.0f, 0.0f, 0.0f); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.0f); v.color.Set(1.0f, 0.0f, 0.0f); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.0f); v.color.Set(1.0f, 0.0f, 0.0f); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.0f); v.color.Set(1.0f, 0.0f, 0.0f); vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);


Mesh* mesh = new Mesh(meshName);

glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
/*glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_bufferdata, GL_STATIC_DRAW);*/
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
mesh->mode = Mesh::DRAW_TRIANGLES;
mesh->indexSize = index_buffer_data.size();
return mesh;
}

void Mesh::Render()
{

}

Mesh* MeshBuilder::GenerateCube(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	const GLfloat vertex_buffer_data[] = {
		0
	};
	const GLfloat color_buffer_data[] = {
		0
	};
	const GLuint index_buffer_data[] = {
		0
	};
	Mesh *mesh = new Mesh(meshName);

	return mesh;
}