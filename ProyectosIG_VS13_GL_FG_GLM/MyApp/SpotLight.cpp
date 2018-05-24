#include "SpotLight.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

SpotLight::SpotLight() : Light(), cutoff(180.0), exponent(0.0)
{
	glm::dvec3 dir(0.0, 0.0, -1.0);
	setDir(dir);
}

SpotLight::SpotLight(GLfloat cut, GLfloat exp, GLfloat x, GLfloat y, GLfloat z) : Light(), cutoff(cut), exponent(exp)
{
	glLightf(id, GL_SPOT_CUTOFF, cutoff);
	glLightf(id, GL_SPOT_EXPONENT, exponent);
	glm::dvec3 dir{ x,y,z };
	setDir(dir);
}

void SpotLight::load(glm::dmat4 const& modelViewMat)
{
	Light::load(modelViewMat);

	glLightf(id, GL_SPOT_CUTOFF, cutoff);
	glLightf(id, GL_SPOT_EXPONENT, exponent);
	glLightfv(id, GL_SPOT_DIRECTION, direction);
}