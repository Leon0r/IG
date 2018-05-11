#include "SpotLight.h"

SpotLight::SpotLight(GLfloat cutoff, GLfloat exponent, GLfloat dir) : Light()
{
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, exponent);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, &dir);
}

SpotLight::~SpotLight()
{

}

void SpotLight::load()
{

}
