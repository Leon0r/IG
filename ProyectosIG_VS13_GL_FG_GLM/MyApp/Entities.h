//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"
#include "Textures.h"
#include "Material.h"
#include "SpotLight.h"
#include "IndexMesh.h"

//-------------------------------------------------------------------------

class Entity
{
public:
	Entity() : modelMat(1.0) { };
	virtual ~Entity() { delete mesh; };

	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update(GLuint timeElapsed) {}

	void setModelMat(glm::dmat4 const& mMat) { modelMat = mMat; }
	void setMaterial(Material const& mt) { material = mt; }
	void setTexture(Texture const& tex) { texture = tex; }

protected:
	Texture texture,
		texture2;
	Material material;
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
	virtual void update(GLuint timeElapsed);
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	void incrementaAngulo() { angle += 5.0; };
};
//-------------------------------------------------------------------------
class Cubo : public Entity
{
public:
	Mesh * mesh2 = nullptr;

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
	virtual ~Poliespiral() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------
class RectangleTex : public Entity
{
public:
	RectangleTex(GLdouble w, GLdouble h);
	RectangleTex(GLdouble w, GLdouble h, GLint numCol, GLint numFil);
	virtual ~RectangleTex() { };
	virtual void draw();
};

//-------------------------------------------------------------------------
class CubeTex : public Entity
{
public:
	Mesh * mesh2 = nullptr;

	CubeTex(GLdouble l);
	virtual ~CubeTex() { };
	virtual void draw();
	virtual void drawTop(); // Pinta los rectangulos de las tapas
	virtual void render(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------
class TriPyramidTex : public Entity
{
public:
	TriPyramidTex(GLdouble r, GLdouble h);
	virtual ~TriPyramidTex() { };
	virtual void draw();
};

//-------------------------------------------------------------------------
class Suelo : public Entity
{
public:
	Suelo(GLdouble w, GLdouble h, GLint repCols, GLint repFils);
	virtual ~Suelo() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------
class GlassPot : public Entity
{
public:
	GlassPot(GLdouble l);
	virtual ~GlassPot() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------
class Grass : public Entity
{
public:
	Grass(GLdouble w, GLdouble h);
	virtual ~Grass() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------
class Foto : public Entity
{
public:
	GLuint timer = 0;
	Foto(GLdouble w, GLdouble h);
	virtual ~Foto() { };
	virtual void update(GLuint timeElapsed);
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------

class Esfera : public Entity
{
public:
	Esfera(GLdouble radio, GLuint meridianos, GLuint paralelos);
	virtual ~Esfera() { gluDeleteQuadric(esfera); }
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);

protected:
	GLUquadricObj * esfera;
	GLdouble radio_;
	GLuint meridianos_,
		paralelos_;
};

//-------------------------------------------------------------------------
class EsferaLuz : public Esfera
{
public:
	EsferaLuz(GLdouble radio, GLuint meridianos, GLuint paralelos);
	virtual ~EsferaLuz() { gluDeleteQuadric(esfera); }
	virtual void update(GLuint timeElapsed);
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	void aumentaAngulo() { ang += 0.1; }
	SpotLight* getSpotLight() { return spotlight; }

protected:
	SpotLight * spotlight;
	Esfera* esferaPeq1;
	Esfera* esferaPeq2;

	Material materialPeq;
	glm::dmat4 modelMatPeq1;
	glm::dmat4 modelMatPeq2;

	GLdouble ang;
	GLdouble tAng;
	GLdouble speed;
	glm::dvec3 T_ang;

	GLdouble cx;
	GLdouble cy;
	GLdouble cz;

	void renderEsferaPeq1(glm::dmat4 const& modelViewMat);
	void renderEsferaPeq2(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------
class Terreno : public Entity
{
public:
	Terreno(std::string fileName);
	Terreno() {};
	virtual ~Terreno() {};

	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void draw();
private:
	IndexMesh * indexMesh;
};
//-------------------------------------------------------------------------
#endif //_H_Entities_H_