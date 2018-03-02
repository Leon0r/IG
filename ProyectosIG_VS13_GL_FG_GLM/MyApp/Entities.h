//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"
#include "Textures.h"

//-------------------------------------------------------------------------

class Entity
{
public:
	Entity() : modelMat(1.0) { };
	virtual ~Entity() { delete mesh; };

	virtual void render(glm::dmat4 const& modelViewMat);

protected:
	Texture texture;
	Mesh* mesh = nullptr;
	glm::dmat4 modelMat;
	virtual void draw();
	virtual void setMvM(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
  EjesRGB(GLdouble l);
  ~EjesRGB() { };
  virtual void draw();
};

//-------------------------------------------------------------------------
class Triangle : public Entity
{
public:
	Triangle(GLdouble r);
	~Triangle() { };
	virtual void draw();
};
//-------------------------------------------------------------------------
class TriangleRGB : public Entity
{
public:
	TriangleRGB(GLdouble r);
	~TriangleRGB() { };
	virtual void draw();
};
//-------------------------------------------------------------------------
class TriPyramid : public Entity
{
public:
	TriPyramid(GLdouble r, GLdouble h);
	~TriPyramid() { };
	virtual void draw();
};
//-------------------------------------------------------------------------
class ContCubo : public Entity
{
public:
	ContCubo(GLdouble l);
	~ContCubo() { };
	virtual void draw();
};
//-------------------------------------------------------------------------
class Diabolo : public Entity
{
public:
	GLdouble angle = 0;

	Diabolo(GLdouble r, GLdouble h);
	~Diabolo() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	void incrementaAngulo(){ angle += 5.0; };
};
//-------------------------------------------------------------------------
class Cubo : public Entity
{
public:
	Mesh* mesh2 = nullptr;

	Cubo(GLdouble l);
	~Cubo() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};
//-------------------------------------------------------------------------
class Dragon : public Entity
{
public:
	Dragon(GLuint numVert);
	~Dragon() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};
//-------------------------------------------------------------------------
class Poliespiral : public Entity
{
public:
	Poliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble increAng,
		GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	~Poliespiral() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------
class RectangleTex : public Entity
{
public:
	RectangleTex(GLdouble w, GLdouble h, int corTex);
	~RectangleTex() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------
#endif //_H_Entities_H_