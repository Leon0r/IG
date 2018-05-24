#include "SpotLight.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

SpotLight::SpotLight(GLfloat cutoff, GLfloat exponent, GLfloat dir) : Light()
{
	glLightf(id, GL_SPOT_CUTOFF, cutoff);
	glLightf(id, GL_SPOT_EXPONENT, exponent);
	glLightfv(id, GL_SPOT_DIRECTION, value_ptr(dir));
}

void SpotLight::load(glm::dmat4 const& modelViewMat)
{
	Light::load(modelViewMat);

	glLightf(id, GL_SPOT_CUTOFF, cutoff);
	glLightf(id, GL_SPOT_EXPONENT, exponent);
	glLightfv(id, GL_SPOT_DIRECTION, value_ptr(dir));
}

void SpotLight::setDirection(GLfloat x, GLfloat y, GLfloat z)
{
	directionX = x;
	directionY = y;
	directionZ = z;
}