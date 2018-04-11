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
	viewMat = lookAt(eye, look, up);
	setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D()
{
	eye = dvec3(500, 500, 500);
	look = dvec3(0, 10, 0);
	up = dvec3(0, 1, 0);
	viewMat = lookAt(eye, look, up);
	setVM();
}

//-------------------------------------------------------------------------

// Desplaza la camara sin cambiar la direccion de vista: Left/ Right
void Camera::moveLR(GLdouble cs)
{

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

}

// Rota la direccion de vista de la camara sin modificar su posicion 
void Camera::rotatePY(GLdouble incrPitch, GLdouble incrYaw) // Valores entre 0 y 360 grados
{
	// Actualizar los angulos
	// pitch += incrPitch;
	// yaw += incrYaw;

	// Limitar los angulos
	// if (pitch > 89.5)
	//	 pitch = 59.5;

	// ...

	// Actualizar la direccion de vista
	/*front.x = sin(radians(yaw)) * cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = -cos(radians(yaw)) * cos(radians(pitch));
	front = glm::normalize(front);
	viewMat = lookAt(eye, eye + front, up);*/

	// ...
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
}
//-------------------------------------------------------------------------

void Camera::yaw(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
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