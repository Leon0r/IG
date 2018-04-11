#pragma once
#include <iostream>
#include <GL/freeglut.h>
#include <glm.hpp>
#include "Pixmap32RGBA.h"

class Texture // utiliza la clase PixMap32RGBA para el método load
{
public:
	Texture() : w(0), h(0), id(0) {};
	~Texture() { if (id != 0) glDeleteTextures(1, &id); };
	bool load(const std::string & BMP_Name, GLubyte alpha = 255);

	// cargar y transferir a openGL
	void bind();
	void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };
protected:
	GLuint w, h; // dimensiones de la imagen
	GLuint id; // identificador interno (GPU) de la textura
	void init();
};

