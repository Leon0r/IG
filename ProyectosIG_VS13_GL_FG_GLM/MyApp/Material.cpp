#include "Material.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

Material::Material()
{
}

Material::~Material()
{
}

void Material::load()
{
	glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(face, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(face, GL_SPECULAR, value_ptr(specular));
	glMaterialf(face, GL_SHININESS, expF);
	glShadeModel(sh);
}

void Material::materialData(MaterialType material)
{
	switch (material)
	{
	case Material::obsidian:
		ambient = { 0.05375, 0.05, 0.06625, 1 };
		diffuse = { 0.18275, 0.17, 0.22525, 1 };
		specular = { 0.332741, 0.328634, 0.346435, 1 };
		expF = 38.4;
		break;
	case Material::turquoise:
		ambient = { 0.1, 0.18725, 0.1745, 1 };
		diffuse = { 0.396, 0.74151, 0.69102, 1 };
		specular = { 0.297254, 0.30829, 0.306678, 1 };
		expF = 12.8;
		break;
	case Material::brass:
		ambient = { 0.329412, 0.223529, 0.027451, 1 };
		diffuse = { 0.780392, 0.568627, 0.113725, 1 };
		specular = { 0.992157, 0.941176, 0.807843, 1 };
		expF = 27.8974;
		break;
	case Material::gold:
		ambient = { 0.24725, 0.1995, 0.0745, 1 };
		diffuse = { 0.75164, 0.60648, 0.22648, 1 };
		specular = { 0.628281, 0.555802, 0.366065, 1 };
		expF = 51.2;
	case Material::silver:
		ambient = { 0.19225, 0.19225, 0.19225, 1 };
		diffuse = { 0.50754, 0.50754, 0.50754, 1 };
		specular = { 0.508273, 0.508273, 0.508273, 1 };
		expF = 51.2;
	case Material::blackPlastic:
		ambient = { 0.0, 0.0, 0.0, 1 };
		diffuse = { 0.01, 0.01, 0.01, 1 };
		specular = { 0.50, 0.50, 0.50, 1 };
		expF = 32;
		break;
	case Material::cyanRubber:
		ambient = { 0.0, 0.05, 0.05, 1 };
		diffuse = { 0.4, 0.5, 0.5, 1 };
		specular = { 0.04, 0.7, 0.7, 1 };
		expF = 10.0;
		break;
	case Material::bronze:
		ambient = { 0.2125, 0.1275, 0.054, 1 };
		diffuse = { 0.714, 0.4284, 0.18144, 1 };
		specular = { 0.393548, 0.271906, 0.166721, 1 };
		expF = 25.6;
		break;
	case Material::chrome:
		ambient = { 0.25, 0.25, 0.25, 1 };
		diffuse = { 0.4, 0.4, 0.4, 1 };
		specular = { 0.774597, 0.774597, 0.774597, 1 };
		expF = 76.8;
		break;
	case Material::copper:
		ambient = { 0.19125, 0.0735, 0.0225, 1 };
		diffuse = { 0.7038, 0.27048, 0.0828, 1 };
		specular = { 0.256777, 0.137622, 0.086014, 1 };
		expF = 12.8;
		break;
	case Material::pewter:
		ambient = { 0.10588, 0.058824, 0.113725, 1 };
		diffuse = { 0.75164, 0.60648, 0.22648, 1 };
		specular = { 0.628251, 0.555802, 0.366065, 1 };
		expF = 51.2;
		break;
	case Material::polishedSilver:
		ambient = { 0.23125, 0.23125, 0.23125, 1 };
		diffuse = { 0.2775, 0.2775, 0.2775, 1 };
		specular = { 0.773911, 0.773911, 0.773911, 1 };
		expF = 89.6;
		break;
	}
}

