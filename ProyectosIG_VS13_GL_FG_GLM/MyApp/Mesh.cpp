#include "Mesh.h"

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
  delete[] vertices;
  delete[] colors;
}
//-------------------------------------------------------------------------

void Mesh::draw() 
{
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate 
    if (colors != nullptr) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate 
    }
	
    glDrawArrays(type, 0, numVertices);   // kind of primitives, first, count

	  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::generateAxesRGB(GLdouble l)
{
  Mesh* m = new Mesh();
  m->type = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);   
  m->vertices[1] = dvec3(l, 0.0, 0);
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0); 
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
 
  return m; 
}
//-------------------------------------------------------------------------
Mesh* Mesh::generateTriangle(GLdouble r)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLES;
	m->numVertices = 3;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(0.0, r, 0.0);
	m->vertices[1] = dvec3(r*cos(radians(30.0)), r*sin(radians(330.0)), 0.0);
	m->vertices[2] = dvec3(r*cos(radians(210.0)), r*sin(radians(330.0)), 0.0);


	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[2] = dvec4(1.0, 0.0, 0.0, 1.0);

	return m;
}
//-------------------------------------------------------------------------
Mesh* Mesh::generateTriangleRGB(GLdouble r)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLES;
	m->numVertices = 3;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(0.0, r, 0.0);
	m->vertices[1] = dvec3(r*cos(radians(30.0)), r*sin(radians(330.0)), 0.0);
	m->vertices[2] = dvec3(r*cos(radians(210.0)), r*sin(radians(330.0)), 0.0);


	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}
//-------------------------------------------------------------------------
Mesh* Mesh::generateTriPyramid(GLdouble r, GLdouble h)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_FAN;
	m->numVertices = 5;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(0.0, r, 0.0);
	m->vertices[1] = dvec3(r*cos(radians(30.0)), r*sin(radians(330.0)), 0.0);
	m->vertices[2] = dvec3(r*cos(radians(210.0)), r*sin(radians(330.0)), 0.0);
	m->vertices[3] = dvec3(0.0, r*sin(radians(0.0)), h);
	m->vertices[4] = dvec3(r*cos(radians(30.0)), r*sin(radians(330.0)), 0.0);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(0.0, 1.0, 1.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 1.0, 1.0);
	m->colors[2] = dvec4(0.0, 1.0, 1.0, 1.0);
	m->colors[3] = dvec4(0.0, 1.0, 1.0, 1.0);
	m->colors[4] = dvec4(0.0, 1.0, 1.0, 1.0);

	return m;
}
//-------------------------------------------------------------------------
Mesh* Mesh::generateContCubo(GLdouble l)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_STRIP;
	m->numVertices = 10;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(l / 2, l / 2, l / 2);
	m->vertices[1] = dvec3(l / 2, -l / 2, l / 2);

	m->vertices[2] = dvec3(-l / 2, l / 2, l / 2);
	m->vertices[3] = dvec3(-l / 2, -l / 2, l / 2);

	m->vertices[4] = dvec3(-l / 2, l / 2, -l / 2);
	m->vertices[5] = dvec3(-l / 2, -l / 2, -l / 2);

	m->vertices[6] = dvec3(l / 2, l / 2, -l / 2);
	m->vertices[7] = dvec3(l / 2, -l / 2, -l / 2);

	m->vertices[8] = dvec3(l / 2, l / 2, l / 2);
	m->vertices[9] = dvec3(l / 2, -l / 2, l / 2);


	m->colors = new dvec4[m->numVertices];

	for (int i = 0; i < m->numVertices; i++){
		m->colors[i] = dvec4(0.0, 0.0, 0.0, 1.0);
	}
	return m;
}
//-------------------------------------------------------------------------
Mesh* Mesh::generateRectangle(GLdouble w, GLdouble h)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_STRIP;
	m->numVertices = 4;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(-w / 2, h / 2, 0);
	m->vertices[1] = dvec3(-w / 2, -h / 2, 0);

	m->vertices[2] = dvec3(w / 2, h / 2, 0);
	m->vertices[3] = dvec3(w / 2, -h / 2, 0);

	m->colors = new dvec4[m->numVertices];

	for (int i = 0; i < m->numVertices; i++){
		m->colors[i] = dvec4(0.0, 0.0, 0.0, 1.0);
	}
	return m;
}
//-------------------------------------------------------------------------
Mesh* Mesh::generateDragon(GLuint numVert){
	Mesh* m = new Mesh();
	m->type = GL_POINTS;
	m->numVertices = numVert;
	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(0.0, 0.0, 0.0);
	
	double auxX, auxY;
	for (int i = 1; i < m->numVertices; i++){
		auxX = m->vertices[i - 1].x;
		auxY = m->vertices[i - 1].y;

		TDragon(auxX, auxY);

		m->vertices[i] = dvec3(auxX, auxY, 0.0);
	}

	m->colors = new dvec4[m->numVertices];

	for (int i = 0; i < m->numVertices; i++){
		m->colors[i] = dvec4(0.0, 0.0, 0.0, 1.0);
	}
	return m;
}
//-------------------------------------------------------------------------

void Mesh::TDragon(double& x, double& y){
	double PR1 = 0.787473;

	double azar = rand() / double(RAND_MAX);

	if (azar < PR1)
		T1(x, y);
	else
		T2(x, y);
}
void Mesh::T1(double& x, double& y){
	x = 0.824074 * x + 0.281482 * y - 0.882290;
	y = - 0.212346 * x + 0.864198 * y - 0.110607;
}
void Mesh::T2(double& x, double& y){
	x = 0.088272 * x + 0.520988 * y + 0.785360;
	y = -0.463889 * x - 0.377778 * y + 8.095795;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generatePoliespiral(dvec2 verIni, GLdouble angIni, GLdouble increAng,
	GLdouble ladoIni, GLdouble incrLado, GLuint numVert){
	Mesh* m = new Mesh();
	m->type = GL_LINE_STRIP;
	m->numVertices = numVert;

	m->colors = new dvec4[m->numVertices];

	for (int i = 0; i < m->numVertices; i++){
		m->colors[i] = dvec4(0.0, 0.0, 0.0, 1.0);
	}
	return m;
}
//-------------------------------------------------------------------------