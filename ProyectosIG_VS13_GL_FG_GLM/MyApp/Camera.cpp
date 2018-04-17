#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Viewport::setSize(GLsizei aw, GLsizei ah)
{
	w = aw;
	h = ah;
	set();
}
 //-------------------------------------------------------------------------

void Viewport::setPosition(GLsizei ax, GLsizei ay) 
{
	x = ax;
	y = ay;
	set();
}
 //-------------------------------------------------------------------------

void Viewport::set()
{
	glViewport(x, y, w, h);
}
//-------------------------------------------------------------------------

void Camera::setAZ()
{
	eye = dvec3(0, 0, 500);
	look = dvec3(0, 0, 0);
	up = dvec3(0, 1, 0);
	front = -normalize(eye - look);
	right = normalize(cross(up, -front));
	// Reasigna los angulos de la camara
	pitchCam = 0;
	yawCam = 0;

	viewMat = lookAt(eye, eye + front, up);
	setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D()
{
	eye = dvec3(500, 500, 500);
	look = dvec3(0, 10, 0);
	up = dvec3(0, 1, 0);
	front = -normalize(eye - look);
	right = normalize(cross(up, -front));
	// Reasigna los angulos de la camara
	pitchCam = degrees(asin(front.y));
	yawCam = degrees(asin(front.x / cos(radians(pitchCam))));

	viewMat = lookAt(eye, eye + front, up);
	setVM();
}
//-------------------------------------------------------------------------

// Cambia de proyeccion ortogonal a perspectiva
void Camera::setPML()
{
	if (orto) 
	{
		glMatrixMode(GL_PROJECTION);
		projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
		glLoadMatrixd(value_ptr(projMat));
		glMatrixMode(GL_MODELVIEW);
	}
	else 
	{
		nearVal = yTop;
		glMatrixMode(GL_PROJECTION);
		projMat = frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
		glLoadMatrixd(value_ptr(projMat));
		glMatrixMode(GL_MODELVIEW);
	}
}

void Camera::setPrj()
{
	orto = !orto;
	setPML();
}

//-------------------------------------------------------------------------

// Desplaza la camara sin cambiar la direccion de vista: Left/ Right
void Camera::moveLR(GLdouble cs)
{
	eye = eye + (right * cs);
	viewMat = lookAt(eye, eye + front, up);
}

// Desplaza la camara sin cambiar la direccion de vista: Forward / Backward
void Camera::moveFB(GLdouble cs)
{
	eye = eye + (front * cs);
	viewMat = lookAt(eye, eye + front, up);
}

// Desplaza la camara sin cambiar la direccion de vista: Up / down
void Camera::moveUD(GLdouble cs)
{
	eye = eye + (up * cs);
	viewMat = lookAt(eye, eye + front, up);
}

// Rota la direccion de vista de la camara sin modificar su posicion (para el raton)
void Camera::rotatePY(GLdouble incrPitch, GLdouble incrYaw) // Valores entre 0 y 360 grados
{
	// Actualizar los angulos
	pitchCam += incrPitch;
	yawCam += incrYaw;

	// Limitar los angulos
	if (pitchCam > 89.5)
		 pitchCam = 89.5;

	else if (pitchCam <= -89.5)
		pitchCam = -89.5;

	if (yawCam >= 360)
		yawCam -= 360;

	// Actualizar la direccion de vista
	front.x = sin(radians(yawCam)) * cos(radians(pitchCam));
	front.y = sin(radians(pitchCam));
	front.z = -cos(radians(yawCam)) * cos(radians(pitchCam));
	front = glm::normalize(front);

	right = glm::normalize(cross(up, -front));

	viewMat = lookAt(eye, eye + front, up);
}

//-------------------------------------------------------------------------

void Camera::setVM()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
	rotatePY(a, 0); // Guarda la ultima pos
}
//-------------------------------------------------------------------------

void Camera::yaw(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
	rotatePY(0, a); // Guarda la ultima pos
}
//-------------------------------------------------------------------------

void Camera::roll(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
}
//-------------------------------------------------------------------------

void Camera::scale(GLdouble s)
{
	factScale -= s;
	if (s < 0) s = 0.01;
	setPM();
}
//-------------------------------------------------------------------------

void Camera::setSize(GLdouble aw, GLdouble ah)
{
	xRight = aw / 2.0;
	xLeft = -xRight;
	yTop = ah / 2.0;
	yBot = -yTop;

	setPM();
}
//-------------------------------------------------------------------------

void Camera::setPM()
{
	projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(projMat));
	glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------