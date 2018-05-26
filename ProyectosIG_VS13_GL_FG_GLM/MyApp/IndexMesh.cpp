#include "IndexMesh.h"
#include <iostream>
#include <fstream>

IndexMesh::IndexMesh() : Mesh(), indices(nullptr), numIndices(0)
{
	type = GL_TRIANGLES;
}

IndexMesh::~IndexMesh()
{
	delete[] indices;
}

void IndexMesh::draw()
{
	if (vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vertices);
		if (colors != nullptr) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, colors);
		}
		if (coordsTexture != nullptr) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, coordsTexture);
		}
		if (normals != nullptr) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, normals);
		}
		if (indices != nullptr) {
			glEnableClientState(GL_INDEX_ARRAY);
			glIndexPointer(GL_UNSIGNED_INT, 0, indices);
		}

		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, indices);

		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_INDEX_ARRAY);
	}
}

// Genera el array de vertices y el array de indices de una cuadrícula centrada en el plano y = 0
// lado (dimensiones totales de la cuadricula) y numDiv (celdas en las que se divide por fila y por columna))
IndexMesh * IndexMesh::generateGrid(GLdouble lado, GLuint numDiv)
{
	IndexMesh* m = new IndexMesh();

	GLdouble incr = lado / numDiv;		// Incremento para la coordenada x, y la z
	GLuint numVer = numDiv + 1;			// Num. de vértices por filas y por columnas

	// Genera vertices
	m->numVertices = numVer * numVer;
	m->vertices = new glm::dvec3[m->numVertices];

	GLint x = -lado / 2;
	GLint y = 0;
	GLint z = -lado / 2;

	for (int i = 0; i < numVer; i++)
	{
		x = -lado / 2;

		for (int j = 0; j < numVer; j++)
		{
			m->vertices[(i * numVer) + j] = glm::dvec3(x, y, z);
			x += incr;
		}

		z += incr;
	}

	// Genera indices
	m->numIndices = numDiv*numDiv * 6;
	m->indices = new GLuint[m->numIndices];

	GLuint i = 0;
	GLuint iv = 0;

	for (int f = 0; f < numDiv; f++)
	{
		for (int c = 0; c < numDiv; c++)
		{
			iv = f * numVer + c;

			m->indices[i] = iv;
			i++;
			m->indices[i] = iv + numVer;
			i++;
			m->indices[i] = iv + 1;
			i++;

			m->indices[i] = iv + 1;
			i++;
			m->indices[i] = iv + numVer;
			i++;
			m->indices[i] = iv + numVer + 1;
			i++;
		}
	}

	return m;

}

// Genera una malla formada por una cuadrícula de lado 256 * 8 y (256 x 256) celdas.
IndexMesh * IndexMesh::generateTerrain(std::string fileName)
{
	std::ifstream file(fileName, std::ios::binary);
	if (!file.is_open()) return nullptr;

	GLuint nDiv = 256;
	GLdouble lado = nDiv * 8;

	GLuint nVer = nDiv + 1;

	IndexMesh* m = generateGrid(lado, nDiv);
	unsigned char * data = new unsigned char[m->numVertices];
	file.read((char *)data, m->numVertices * sizeof(char));
	file.close();

	for (GLuint i = 0; i < m->numVertices; i++)
	{
		m->vertices[i].y = data[i] * 0.5;
	}

	m->coordsTexture = new glm::dvec2[m->numVertices];
	for (int f = 0; f < nVer; f++) {
		for (int c = 0; c > nVer; c++) {
			m->coordsTexture[f * nVer + c] = glm::dvec2(c*1.0 / nDiv, 1 - f * 1.0 / nDiv);
		}
	}

	delete data;

	m->normals = new glm::dvec3[m->numVertices];

	glm::dvec3 a;
	glm::dvec3 b;
	glm::dvec3 c;
	glm::dvec3 n;

	for (int i = 0; i < m->numVertices; i++)
	{
		m->normals[i].x = 0;
		m->normals[i].y = 0;
		m->normals[i].z = 0;
	}

	for (int i = 0; i < m->numVertices; i += 3)
	{
		a = { m->vertices[i].x, m->vertices[i].y, m->vertices[i].z };
		b = { m->vertices[i + 1].x, m->vertices[i + 1].y, m->vertices[i + 1].z };
		c = { m->vertices[i + 2].x, m->vertices[i + 2].y, m->vertices[i + 2].z };
		n = glm::normalize(glm::cross(b - a, c - a));

		for (int j = 0; j <= 2; j++) {
			m->normals[i + j].x += n.x;
			m->normals[i + j].y += n.y;
			m->normals[i + j].z += n.z;
			glm::normalize(m->normals[i + j]);
		}
	}

	return m;
}
