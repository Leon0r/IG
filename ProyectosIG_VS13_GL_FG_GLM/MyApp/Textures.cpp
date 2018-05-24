#include "Textures.h"

bool Texture::load(const std::string & BMP_Name, GLubyte alpha){

	if (id == 0) 
		init();

	PixMap32RGBA pixMap; // Var. local para cargar la imagen del archivo
	pixMap.load_bmp24BGR(BMP_Name); // Carga y añade alpha=255

	// Carga correcta ?
	if (alpha != 255) 
		pixMap.set_alpha(alpha);

	w = pixMap.width();
	h = pixMap.height();
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, pixMap.data());
	// Transferir a openGL

	return true;
}

bool Texture::load(const std::string & BMP_Name, glm::ivec3 color, GLubyte alpha) {

	if (id == 0)
		init();

	PixMap32RGBA::rgba_color color2 = { color.r, color.g, color.b, alpha };

	PixMap32RGBA pixMap; // Var. local para cargar la imagen del archivo

	pixMap.load_bmp24BGR(BMP_Name); // Carga y añade alpha=255

	// Carga correcta ?
	if (alpha != 255)
		pixMap.set_colorkey_alpha(color2, alpha);

	w = pixMap.width();
	h = pixMap.height();
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, pixMap.data());
	// Transferir a openGL

	return true;
}

// Carga en la imagen de la textura la imagen del Color Buffer
void Texture::loadColorBuffer(GLsizei width, GLsizei height)
{
	// init(); // Esto carga la textura como el texture.load(BMP_NAME)

	glReadBuffer(GL_FRONT);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
	  0, 0, width, height, 0); // En coordenadas de pantalla (como el puerto de vista)
	glReadBuffer(GL_FRONT);
}

// Utiliza una variable PixMap32RGBA para crear un buffer del tamano de la textura
void Texture::save(const std::string & BMP_Name)
{
	PixMap32RGBA textures;
	textures.create_pixmap(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, textures.data());
	textures.save_bmp24BGR(BMP_Name);
}

void Texture::bind(GLint mix){
	glBindTexture(GL_TEXTURE_2D, id); // Activa la textura
	// La función de mezcla de colores no queda guardada en el objeto
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mix);
}

void Texture::init(){
	glGenTextures(1, &id); // Genera un identificador para una nueva textura
	glBindTexture(GL_TEXTURE_2D, id); // Filters and clamping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}