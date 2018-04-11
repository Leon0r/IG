#include "Entities.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::render(dmat4 const& modelViewMat) 
{ 
	setMvM(modelViewMat); 
	draw(); 
}
//-------------------------------------------------------------------------

void Entity::draw() 
{ 
  if (mesh != nullptr) 
    mesh -> draw(); 
}
//-------------------------------------------------------------------------

void Entity::setMvM(dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
  mesh = Mesh::generateAxesRGB(l);
}

void EjesRGB::draw()
{
  glLineWidth(2);
  mesh->draw();
  glLineWidth(1);
}
//-------------------------------------------------------------------------

Triangle::Triangle(GLdouble r) : Entity()
{
	mesh = Mesh::generateTriangle(r);
}

void Triangle::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

TriangleRGB::TriangleRGB(GLdouble r) : Entity()
{
	mesh = Mesh::generateTriangleRGB(r);
}

void TriangleRGB::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

TriPyramid::TriPyramid(GLdouble r, GLdouble h) : Entity()
{
	mesh = Mesh::generateTriPyramid(r, h);
}

void TriPyramid::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

ContCubo::ContCubo(GLdouble l) : Entity()
{
	mesh = Mesh::generateContCubo(l);
}

void ContCubo::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

Diabolo::Diabolo(GLdouble r, GLdouble h) : Entity()
{
	mesh = Mesh::generateTriPyramidTex(r, h, 0);
	texture.load("..\\Bmps\\floris.bmp"); // cargamos la imagen

	modelMat = translate(modelMat, dvec3(+200.0, r + 1.0 , 0.0));
}

void Diabolo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	texture.bind();
	mesh->draw();
	texture.unbind();
}

void Diabolo::render(dmat4 const& modelViewMat){
	modelMat = rotate(modelMat, angle, dvec3(0, 0, 1)); // Para girarlo con la 'G'

	dmat4 aMat = modelViewMat*modelMat;

	aMat = translate(aMat, dvec3(0, 0, -200.0));
	glLoadMatrixd(value_ptr(aMat));

	draw();

	
	aMat = rotate(aMat, radians(60.0), dvec3(0, 0, 1));
	glLoadMatrixd(value_ptr(aMat));

	draw();

	aMat = translate(aMat, dvec3(0, 0, 400.0));
	aMat = rotate(aMat, radians(180.0), dvec3(0, 1, 0));
	glLoadMatrixd(value_ptr(aMat));

	draw();

	aMat = rotate(aMat, radians(60.0), dvec3(0, 0, 1));
	glLoadMatrixd(value_ptr(aMat));

	draw();
}
//-------------------------------------------------------------------------

Cubo::Cubo(GLdouble l) : Entity()
{
	mesh = Mesh::generateContCubo(l);
	mesh2 = Mesh::generateRectangle(l, l);
}

void Cubo::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_BACK, GL_POINT);
	glLineWidth(1);
}

void Cubo::render(dmat4 const& modelViewMat){
	
	dmat4 aMat = modelViewMat*modelMat;
	mesh->draw();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	aMat = modelViewMat*modelMat;

	aMat = rotate(aMat, radians(-90.0), dvec3(1, 0, 0));
	aMat = translate(aMat, dvec3(0, 0, -100.0));
	aMat = rotate(aMat, radians(180.0), dvec3(0, 1, 0));

	glLoadMatrixd(value_ptr(aMat));
	mesh2->draw();

	aMat = modelViewMat*modelMat;

	aMat = rotate(aMat, radians(90.0), dvec3(1, 0, 0));
	aMat = rotate(aMat, radians(45.0), dvec3(0, -1, 0));
	aMat = translate(aMat, dvec3(-100.0, 0.0, -140.0));
	aMat = rotate(aMat, radians(180.0), dvec3(1, 0, 0));
	glLoadMatrixd(value_ptr(aMat));
	mesh2->draw();
}
//-------------------------------------------------------------------------

Dragon::Dragon(GLuint numVert) : Entity()
{
	mesh = Mesh::generateDragon(numVert);
}

void Dragon::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINTS);
	mesh->draw();
	glLineWidth(1);
}

void Dragon::render(dmat4 const& modelViewMat){
	dmat4 aMat = modelViewMat*modelMat;
	aMat = translate(aMat, dvec3(-40.0, -170.0, 0.0));
	aMat = scale(aMat, dvec3(40.0, 40.0, 0.0));
	
	Entity::render(aMat);
}
//-------------------------------------------------------------------------

Poliespiral::Poliespiral(dvec2 verIni, GLdouble angIni, GLdouble increAng,
	GLdouble ladoIni, GLdouble incrLado, GLuint numVert) : Entity()
{
	mesh = Mesh::generatePoliespiral(verIni, angIni, increAng,
		ladoIni, incrLado, numVert);
}

void Poliespiral::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glLineWidth(1);
}

void Poliespiral::render(dmat4 const& modelViewMat){
	dmat4 aMat = modelViewMat*modelMat;
	aMat = scale(aMat, dvec3(10.0, 10.0, 0.0));

	Entity::render(aMat);
}
//-------------------------------------------------------------------------

RectangleTex::RectangleTex(GLdouble w, GLdouble h, int corTex) : Entity()
{
	mesh = Mesh::generateRectangleTex(w, h, corTex); // con coord. de textura
	texture.load("..\\Bmps\\Zelda.bmp"); // cargamos la imagen
}

RectangleTex::RectangleTex(GLdouble w, GLdouble h, GLint numCol, GLint numFil, int corTex){
	mesh = Mesh::generateRectangleTex(w, h, numCol, numFil,  corTex); // con coord. de textura
	texture.load("..\\Bmps\\Zelda.bmp"); // cargamos la imagen
}

void RectangleTex::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	texture.bind();
	mesh->draw();
	texture.unbind();
}
//-------------------------------------------------------------------------

CubeTex::CubeTex(GLdouble l, int corTex){
	
	mesh = Mesh::generateContCuboTex(l, corTex);
	mesh2 = Mesh::generateRectangleTex(l, l, corTex);
	// Cargamos las imagenes
	texture.load("..\\Bmps\\container.bmp");
	texture2.load("..\\Bmps\\chuches.bmp");

	modelMat = translate(modelMat, dvec3(-200.0, (l / 2) + 1.0, 0.0)); // Situa el cubo sobre "el suelo"
}

void CubeTex::draw()
{
	glCullFace(GL_FRONT);
	texture.bind();
	mesh->draw();
	texture.unbind();

	glCullFace(GL_BACK);
	texture2.bind();
	mesh->draw();
	texture2.unbind();
}

void CubeTex::drawTop()
{
	glCullFace(GL_FRONT);
	texture.bind();
	mesh2->draw();
	texture.unbind();

	glCullFace(GL_BACK);
	texture2.bind();
	mesh2->draw();
	texture2.unbind();
}

void CubeTex::render(dmat4 const& modelViewMat)
{
	glEnable(GL_CULL_FACE);
	
	dmat4 aMat = modelViewMat*modelMat;

	glLoadMatrixd(value_ptr(aMat));
	draw();

	aMat = modelViewMat*modelMat;

	aMat = rotate(aMat, radians(-90.0), dvec3(1, 0, 0));
	aMat = translate(aMat, dvec3(0, 0, -100.0));

	glLoadMatrixd(value_ptr(aMat));	
	drawTop();

	aMat = modelViewMat*modelMat;

	aMat = rotate(aMat, radians(90.0), dvec3(1, 0, 0));
	aMat = rotate(aMat, radians(45.0), dvec3(0, -1, 0));
	aMat = translate(aMat, dvec3(-100.0, 0.0, -140.0));
	glLoadMatrixd(value_ptr(aMat));

	drawTop();

	glDisable(GL_CULL_FACE);
}

//-------------------------------------------------------------------------

TriPyramidTex::TriPyramidTex(GLdouble r, GLdouble h, int corTex) : Entity()
{
	mesh = Mesh::generateTriPyramidTex(r, h, corTex); // con coord. de textura
	texture.load("..\\Bmps\\Zelda.bmp"); // cargamos la imagen
}

void TriPyramidTex::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	texture.bind();
	mesh->draw();
	texture.unbind();
}

//-------------------------------------------------------------------------

Suelo::Suelo(GLdouble w, GLdouble h, GLint repCols, GLint repFils, int corTex) : Entity() {
	mesh = Mesh::generateRectangleTex(w, h, repCols, repFils, corTex); // con coord. de textura
	texture.load("..\\Bmps\\baldosaC.bmp"); // cargamos la imagen

	modelMat = rotate(modelMat, radians(90.0), dvec3(1, 0, 0)); // Define la matriz de modo que sea horizontal
}

void Suelo::draw()
{
	texture.bind();
	mesh->draw();
	texture.unbind();
}

void Suelo::render(dmat4 const& modelViewMat)
{
	glEnable(GL_REPEAT);
	dmat4 aMat = modelViewMat*modelMat;
	glLoadMatrixd(value_ptr(aMat));
	draw();
	glDisable(GL_REPEAT);
}
//-------------------------------------------------------------------------
