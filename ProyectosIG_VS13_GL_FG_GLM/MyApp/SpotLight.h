#pragma once
#include "Light.h"

class SpotLight : public Light
{
public:
	SpotLight(GLfloat cutoff, GLfloat exponent, GLfloat dir);
	~SpotLight();

	virtual void load();
};

