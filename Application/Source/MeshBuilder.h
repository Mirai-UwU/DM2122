#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, float size = 1.0f);
	static Mesh* GenerateCube(const std::string& meshName, Color color, float length);
	static Mesh* GenerateCircle(const std::string& meshName, Color color, unsigned numSlice, float radius = 1.f);
	static Mesh* GenerateSphere(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius = 1.f);
};

#endif