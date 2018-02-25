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
//-------------------------------------------------------------------------

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
//-------------------------------------------------------------------------

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
//-------------------------------------------------------------------------

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
//-------------------------------------------------------------------------

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
//-------------------------------------------------------------------------

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
	mesh = Mesh::generateTriPyramid(r, h);
}
//-------------------------------------------------------------------------

void Diabolo::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glLineWidth(1);
}

void Diabolo::render(dmat4 const& modelViewMat){
	dmat4 aMat = modelViewMat*modelMat;
	aMat = translate(aMat, dvec3(0, 0, -100.0));
	aMat = rotate(aMat, angle, dvec3(0, 0, 1));
	aMat = rotate(aMat, radians(0.0), dvec3(0, 0, 1));
	Entity::render(aMat);
	aMat = translate(aMat, dvec3(0, 0, 0.0));
	aMat = rotate(aMat, angle, dvec3(0, 0, 1));
	aMat = rotate(aMat, radians(60.0), dvec3(0, 0, 1));
	Entity::render(aMat);

	aMat = rotate(aMat, radians(180.0), dvec3(0, 1, 0));

	aMat = translate(aMat, dvec3(0, 0, -200.0));
	aMat = rotate(aMat, angle, dvec3(0, 0, 1));
	aMat = rotate(aMat, radians(0.0), dvec3(0, 0, 1));
	Entity::render(aMat);
	aMat = translate(aMat, dvec3(0, 0, 0.0));
	aMat = rotate(aMat, angle, dvec3(0, 0, 1));
	aMat = rotate(aMat, radians(60.0), dvec3(0, 0, 1));
	Entity::render(aMat);
}
//-------------------------------------------------------------------------
void Diabolo::incrementaAngulo(){
	angle += 5.0;
}
//-------------------------------------------------------------------------
Cubo::Cubo(GLdouble l) : Entity()
{
	mesh = Mesh::generateContCubo(l);
	mesh2 = Mesh::generateRectangle(l, l);
}
//-------------------------------------------------------------------------

void Cubo::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glPolygonMode(GL_BACK, GL_POINT);
	mesh2->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------
void Cubo::render(dmat4 const& modelViewMat){
	dmat4 aMat = modelViewMat*modelMat;
	aMat = translate(aMat, dvec3(0, 0, -100.0));
	aMat = rotate(aMat, radians(0.0), dvec3(0, 0, 1));
	Entity::render(aMat);
	aMat = translate(aMat, dvec3(0, 0, 0.0));
	aMat = rotate(aMat, radians(60.0), dvec3(0, 0, 1));
	Entity::render(aMat);

	aMat = rotate(aMat, radians(180.0), dvec3(0, 1, 0));

	aMat = translate(aMat, dvec3(0, 0, -200.0));
	aMat = rotate(aMat, radians(0.0), dvec3(0, 0, 1));
	Entity::render(aMat);
	aMat = translate(aMat, dvec3(0, 0, 0.0));
	aMat = rotate(aMat, radians(60.0), dvec3(0, 0, 1));
	Entity::render(aMat);
}
//-------------------------------------------------------------------------

Dragon::Dragon(GLuint numVert) : Entity()
{
	mesh = Mesh::generateDragon(numVert);
}
//-------------------------------------------------------------------------

void Dragon::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINTS);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

Poliespiral::Poliespiral(dvec2 verIni, GLdouble angIni, GLdouble increAng,
	GLdouble ladoIni, GLdouble incrLado, GLuint numVert) : Entity()
{
	mesh = Mesh::generatePoliespiral(verIni, angIni, increAng,
		ladoIni, incrLado, numVert);
}
//-------------------------------------------------------------------------

void Poliespiral::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------