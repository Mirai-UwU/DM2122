#ifndef UTILITY_H
#define utility_h

#include "Mesh.h"
#include "Vertex.h"
#include "Mtx44.h"

Position operator*(const Mtx44& lhs, const Position& rhs);
#endif