//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

//-------------------------------------------------------------------------

class Mesh
{
public:
	static Mesh* generateAxesRGB(GLdouble l);
	static Mesh* generateTriangle(GLdouble r);
	static Mesh* generateTriangleRGB(GLdouble r);
	static Mesh* generateTriPyramid(GLdouble r, GLdouble h);
	static Mesh* generateContCubo(GLdouble l);
	static Mesh* generateRectangle(GLdouble w, GLdouble h);
	static Mesh* generateDragon(GLuint numVert);
	static Mesh* generatePoliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble increAng,
		GLdouble ladoIni, GLdouble incrLado, GLuint numVert);

	static Mesh* generateRectangleTex(GLdouble w, GLdouble h);
	static Mesh* generateRectangleTex(GLdouble w, GLdouble h, GLint repCols, GLint repFils);
	static Mesh* generateTriPyramidTex(GLdouble r, GLdouble h);
	static Mesh* generateContCuboTex(GLdouble l);

	Mesh(void) { };
	virtual ~Mesh(void);
	virtual void draw();
	glm::dvec3* getVertices() { return vertices; };
	glm::dvec4* getColours() { return colors; };
	glm::dvec2* getTexCoords() { return coordsTexture; };

protected:
	GLuint numVertices = 0;
	GLuint type = GL_POINTS;

	glm::dvec3* vertices = nullptr;
	glm::dvec4* colors = nullptr;
	glm::dvec2* texture = nullptr;
	glm::dvec2* coordsTexture = nullptr;
	glm::dvec3* normals = nullptr;

	static void TDragon(double& x, double& y);
	static void T1(double& x, double& y);
	static void T2(double& x, double& y);

	static void movePoliespiral(GLdouble& x, GLdouble& y, GLdouble angulo, GLdouble lado);
};
//-------------------------------------------------------------------------
#endif //_H_Scene_H_