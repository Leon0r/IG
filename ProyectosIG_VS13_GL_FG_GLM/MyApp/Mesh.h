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

  Mesh(void) { };
  ~Mesh(void);
  virtual void draw();
  glm::dvec3* getVertices() { return vertices; };
  glm::dvec4* getColours() { return colors; };
   
protected:
   GLuint numVertices = 0;
   GLuint type = GL_POINTS;
   glm::dvec3* vertices = nullptr;
   glm::dvec4* colors = nullptr;

   static void TDragon(double& x, double& y);
   static void T1(double& x, double& y);
   static void T2(double& x, double& y);

   static void movePoliespiral(GLdouble& x, GLdouble& y, GLdouble angulo, GLdouble lado);
};
//-------------------------------------------------------------------------
#endif //_H_Scene_H_