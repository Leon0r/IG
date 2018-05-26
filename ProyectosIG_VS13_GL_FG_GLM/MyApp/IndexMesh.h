#pragma once

#include "Mesh.h"
#include <string>

class IndexMesh : public Mesh
{
public:
	IndexMesh();
	virtual ~IndexMesh();

	virtual void draw();

	// Genera el array de vertices y el array de indices de una cuadrícula centrada en el plano y = 0
	static IndexMesh* generateGrid(GLdouble lado, GLuint numDiv);
	// Genera una malla formada por una cuadrícula de lado 256 * 8 y (256 x 256) celdas.
	static IndexMesh* generateTerrain(std::string fileName);

private:
	GLuint * indices;
	GLuint numIndices;
};

