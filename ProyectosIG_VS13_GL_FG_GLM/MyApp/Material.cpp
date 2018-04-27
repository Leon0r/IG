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
	// ...
	glShadeModel(sh);
}
