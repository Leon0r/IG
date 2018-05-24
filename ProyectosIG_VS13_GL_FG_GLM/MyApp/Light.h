#pragma once

#include <GL/freeglut.h>
#include <glm.hpp>

class Light
{
protected:
	static GLuint cont; // valor inicial cont = 0 en el cpp
	GLuint id = GL_MAX_LIGHTS; // GL_LIGHTi

	glm::fvec4 ambient = { 0.1,0.1,0.1,1 };
	glm::fvec4 diffuse = { 0.5,0.5,0.5,1 };
	glm::fvec4 specular = { 0.5,0.5,0.5,1 };

	glm::fvec4 posDir = { 0,0,1,0 };// w = 0 -> vector

public:
	Light();
	~Light() { disable(); }
	void disable();
	void enable();
	virtual void load(glm::dmat4 const& modelViewMat);

	void setAmb(glm::fvec4 amb) { ambient = amb; }
	void setDif(glm::fvec4 dif) { diffuse = dif; }
	void setSpec(glm::fvec4 spec) { specular = spec; }

	void setPos(glm::fvec3 pos) { posDir = glm::fvec4(pos, 1.0); }
	void setDir(glm::fvec3 dir) { posDir = glm::fvec4(dir, 0.0); } // -dir ?
};

