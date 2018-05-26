//#pragma once
#ifndef _H_Camera_H_
#define _H_Camera_H_

#include <GL/freeglut.h>
#include <glm.hpp>

//-------------------------------------------------------------------------

class Viewport {
public:
	Viewport(GLsizei aw, GLsizei ah) : w(aw), h(ah) { };
	~Viewport() { };

	void setSize(GLsizei aw, GLsizei ah);
	void setPosition(GLsizei ax, GLsizei ay);

	GLsizei getX() { return x; };
	GLsizei getY() { return y; };
	GLsizei getW() { return w; };
	GLsizei getH() { return h; };

protected:
	GLint x = 0, y = 0;
	GLsizei w, h;
	void set();
};

//-------------------------------------------------------------------------

class Camera {
public:
	bool orto = false; // Cambia la proyeccion
	GLdouble pitchCam, yawCam;

	Camera(Viewport* avp) : vp(avp), viewMat(1.0), projMat(1.0),
		xRight(avp->getW() / 2.0), xLeft(-xRight), yTop(avp->getH() / 2.0), yBot(-yTop)
	{ };
	~Camera() {};
	Viewport* getVP() { return vp; }

	glm::dvec3 getPosition() const { return eye; }
	glm::dvec3 getFront(){ return front; }

	// View matrix
	glm::dmat4 const& getViewMat() { return viewMat; };

	void setAZ();  // lookAt(eye(0,0,500), look(0,0,0) up(0, 1, 0))
	void set3D();  // lookAt(eye(500,500,500), look(0,10,0) up(0, 1, 0))

	void setPML(); // Cambia de proyeccion ortogonal a perspectiva
	void setPrj();

	// Desplazan la camara sin cambiar la direccion de vista
	void moveLR(GLdouble cs); // Left/ Right
	void moveFB(GLdouble cs); // Forward / Backward
	void moveUD(GLdouble cs); // Up / down

	// Rota la direccion de vista de la camara sin modificar su posicion 
	void rotatePY(GLdouble incrPitch, GLdouble incrYaw);

	void pitch(GLdouble a); // Rotates a degrees on the X axis
	void yaw(GLdouble a);   // Rotates a degrees on the Y axis
	void roll(GLdouble a);  // Rotates a degrees on the Z axis

	// Projection matrix
	glm::dmat4 const& getProjMat() { return projMat; };

	void setSize(GLdouble aw, GLdouble ah);
	void scale(GLdouble s);

protected:

	glm::dvec3 eye = { 0.0, 0.0, 500.0 };
	glm::dvec3 look = { 0.0, 0.0, 0.0 };
	glm::dvec3 up = { 0.0, 1.0, 0.0 };

	glm::dvec3 front = -normalize(eye - look); // = { 0.0,0.0,0.0 };
	glm::dvec3 right = normalize(cross(up, -front)); // = { 0.0,0.0,0.0 };

	glm::dmat4 viewMat;  // Inverse

	GLdouble xRight, xLeft, yTop, yBot;
	GLdouble nearVal = 1;
	GLdouble farVal = 10000;
	GLdouble factScale = 1;
	glm::dmat4 projMat;

	Viewport* vp;

	void setVM();
	void setPM();
};

//-------------------------------------------------------------------------

#endif //_H_Camera_H_