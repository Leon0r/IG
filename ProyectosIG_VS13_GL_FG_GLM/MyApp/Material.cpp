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
		expF = 0.3;
		break;
	case Material::turquoise:
		ambient = { 0.1, 0.18725, 0.1745, 1 };
		diffuse = { 0.396, 0.74151, 0.69102, 1 };
		specular = { 0.297254, 0.30829, 0.306678, 1 };
		expF = 0.1;
		break;
	case Material::brass:
		ambient = { 0.329412, 0.223529, 0.027451, 1 };
		diffuse = { 0.780392, 0.568627, 0.113725, 1 };
		specular = { 0.992157, 0.941176, 0.807843, 1 };
		expF = 27.8974f;
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
		expF = 0.25;
		break;
	case Material::cyanRubber:
		ambient = { 0.0, 0.05, 0.05, 1 };
		diffuse = { 0.4, 0.5, 0.5, 1 };
		specular = { 0.04, 0.7, 0.7, 1 };
		expF = 0.078125;
		break;
	}
}

