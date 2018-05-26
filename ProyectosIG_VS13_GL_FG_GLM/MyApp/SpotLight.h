#pragma once
#include "Light.h"

#include <GL/freeglut.h>
#include <glm.hpp>

class SpotLight : public Light
{
public:
	SpotLight();
	SpotLight(GLfloat cut, GLfloat exp, GLfloat x, GLfloat y, GLfloat z);
	virtual ~SpotLight() {}

	virtual void load(glm::dmat4 const& modelViewMat);
	void setDirection(GLfloat x, GLfloat y, GLfloat z);
	void setPosPos(glm::dvec3 pospos){ posPos = { pospos.x, pospos.y, pospos.z, 1 }; }

protected:
	GLfloat direction[3];
	GLfloat cutoff,
		exponent;
	glm::fvec4 posPos = { 0, 0, 1, 1 };// w = 0 -> vector
};