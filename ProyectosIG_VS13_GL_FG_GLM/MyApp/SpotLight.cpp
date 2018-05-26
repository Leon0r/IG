#include "SpotLight.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

SpotLight::SpotLight() : Light(), cutoff(180.0), exponent(0.0)
{
	setDirection(0.0, 0.0, -1.0);
}

SpotLight::SpotLight(GLfloat cut, GLfloat exp, GLfloat x, GLfloat y, GLfloat z) : Light(), cutoff(cut), exponent(exp)
{
	glLightf(id, GL_SPOT_CUTOFF, cutoff);
	glLightf(id, GL_SPOT_EXPONENT, exponent);
	setDirection(x, y, z);
	glLightfv(id, GL_SPOT_DIRECTION, direction);
}

void SpotLight::load(glm::dmat4 const& modelViewMat)
{
	Light::load(modelViewMat);

	glLightf(id, GL_SPOT_CUTOFF, cutoff);
	glLightf(id, GL_SPOT_EXPONENT, exponent);
	glLightfv(id, GL_SPOT_DIRECTION, direction);
	glLightfv(id, GL_POSITION, value_ptr(posPos));
}

void SpotLight::setDirection(GLfloat x, GLfloat y, GLfloat z)
{
	direction[0] = x;
	direction[1] = y;
	direction[2] = z;
}