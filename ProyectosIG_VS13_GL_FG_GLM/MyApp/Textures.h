#pragma once
#include <iostream>
#include <GL/freeglut.h>
#include <glm.hpp>
#include "Pixmap32RGBA.h"

class Texture // Utiliza la clase PixMap32RGBA para el método load
{
public:
	Texture() : w(0), h(0), id(0) {};
	~Texture() { if (id != 0) glDeleteTextures(1, &id); };
	bool load(const std::string & BMP_Name, GLubyte alpha = 255);
	
	// Carga en la imagen de la textura la imagen del Color Buffer
	bool loadColorBuffer(GLsizei width, GLsizei height);
	// Utiliza una variable PixMap32RGBA para crear un buffer del tamano de la textura
	bool save(const std::string & BMP_Name);

	// Cargar y transferir a openGL
	void bind();
	void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };
protected:
	GLuint w, h; // Dimensiones de la imagen
	GLuint id; // Identificador interno (GPU) de la textura
	void init();
};

