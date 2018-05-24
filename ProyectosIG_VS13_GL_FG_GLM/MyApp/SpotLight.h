#pragma once
#include "Light.h"

#include <GL/freeglut.h>
#include <glm.hpp>

class SpotLight : public Light
{
public:
	SpotLight(GLfloat cutoff, GLfloat exponent, GLfloat dir);
	~SpotLight() {}

	virtual void load(glm::dmat4 const& modelViewMat);
	void setDirection(GLfloat x, GLfloat y, GLfloat z);

protected:
	GLfloat directionX, 
			directionY, 
			directionZ;
	GLfloat cutoff,
			exponent;
};