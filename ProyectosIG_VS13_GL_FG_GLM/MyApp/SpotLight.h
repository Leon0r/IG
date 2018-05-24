#pragma once
#include "Light.h"

#include <GL/freeglut.h>
#include <glm.hpp>

class SpotLight : public Light
{
public:
	SpotLight();
	SpotLight(GLfloat cut, GLfloat exp, GLfloat x, GLfloat y, GLfloat z);
	~SpotLight() {}

	virtual void load(glm::dmat4 const& modelViewMat);

protected:
	GLfloat direction[3];
	GLfloat cutoff,
			exponent;
};