#pragma once

#include <GL/freeglut.h>
#include <glm.hpp>

class Material
{
public:
	Material();
	~Material();

	glm::fvec4 ambient, diffuse, specular; // Coeficientes de reflexion
	GLfloat expF; // Expenente especular (brillo)
	GLuint face = GL_FRONT_AND_BACK; //Ambos lados
	GLuint sh = GL_SMOOTH; // Smooth shading

	enum MaterialType {
		obsidian, turquoise, brass, gold,
		silver, blackPlastic, cyanRubber,
		bronze, chrome, copper, pewter, polishedSilver
	};

	virtual void load();
	void materialData(MaterialType material);
};

