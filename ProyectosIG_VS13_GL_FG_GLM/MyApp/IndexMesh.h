#pragma once

#include "Mesh.h"
#include <string>

class IndexMesh : public Mesh
{
public:
	IndexMesh();
	virtual ~IndexMesh();

	virtual void draw();

	static IndexMesh* generateGrid(GLdouble lado, GLuint numDiv);
	static IndexMesh* generateTerrain(std::string fileName);

private:
	GLuint * indices;
	GLuint numIndices;
};

