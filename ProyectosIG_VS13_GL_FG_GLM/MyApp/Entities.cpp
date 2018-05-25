#include "Entities.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::render(dmat4 const& modelViewMat)
{
	setMvM(modelViewMat);
	draw();
}
//-------------------------------------------------------------------------

void Entity::draw()
{
	if (mesh != nullptr)
		mesh->draw();
}
//-------------------------------------------------------------------------

void Entity::setMvM(dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l) : Entity()
{
	mesh = Mesh::generateAxesRGB(l);
}

void EjesRGB::draw()
{
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

Triangle::Triangle(GLdouble r) : Entity()
{
	mesh = Mesh::generateTriangle(r);
}

void Triangle::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

TriangleRGB::TriangleRGB(GLdouble r) : Entity()
{
	mesh = Mesh::generateTriangleRGB(r);
}

void TriangleRGB::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

TriPyramid::TriPyramid(GLdouble r, GLdouble h) : Entity()
{
	mesh = Mesh::generateTriPyramid(r, h);
}

void TriPyramid::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

ContCubo::ContCubo(GLdouble l) : Entity()
{
	mesh = Mesh::generateContCubo(l);
}

void ContCubo::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

Diabolo::Diabolo(GLdouble r, GLdouble h) : Entity()
{
	mesh = Mesh::generateTriPyramidTex(r, h);
	texture.load("..\\Bmps\\floris.bmp"); // cargamos la imagen

	modelMat = translate(modelMat, dvec3(50.0, r + 1.0, -200.0));
}

void Diabolo::update(GLuint timeElapsed)
{
	angle = mod(angle + 0.25 * timeElapsed, 360.0);

}

void Diabolo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	texture.bind();
	mesh->draw();
	texture.unbind();
}

void Diabolo::render(dmat4 const& modelViewMat) {
	// modelMat = rotate(modelMat, angle, dvec3(0, 0, 1)); // Para girarlo con la 'G'
	// angle = 0;

	dmat4 aMat = modelViewMat * modelMat;

	aMat = rotate(aMat, radians(angle), dvec3(0, 0, 1));

	aMat = translate(aMat, dvec3(0, 0, -200.0));
	glLoadMatrixd(value_ptr(aMat));

	draw();

	aMat = rotate(aMat, radians(60.0), dvec3(0, 0, 1));
	glLoadMatrixd(value_ptr(aMat));

	draw();

	aMat = translate(aMat, dvec3(0, 0, 400.0));
	aMat = rotate(aMat, radians(180.0), dvec3(0, 1, 0));
	glLoadMatrixd(value_ptr(aMat));

	draw();

	aMat = rotate(aMat, radians(60.0), dvec3(0, 0, 1));
	glLoadMatrixd(value_ptr(aMat));

	draw();
}
//-------------------------------------------------------------------------

Cubo::Cubo(GLdouble l) : Entity()
{
	mesh = Mesh::generateContCubo(l);
	mesh2 = Mesh::generateRectangle(l, l);
}

void Cubo::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_BACK, GL_POINT);
	glLineWidth(1);
}

void Cubo::render(dmat4 const& modelViewMat) {

	dmat4 aMat = modelViewMat * modelMat;
	mesh->draw();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	aMat = modelViewMat * modelMat;

	aMat = rotate(aMat, radians(-90.0), dvec3(1, 0, 0));
	aMat = translate(aMat, dvec3(0, 0, -100.0));
	aMat = rotate(aMat, radians(180.0), dvec3(0, 1, 0));

	glLoadMatrixd(value_ptr(aMat));
	mesh2->draw();

	aMat = modelViewMat * modelMat;

	aMat = rotate(aMat, radians(90.0), dvec3(1, 0, 0));
	aMat = rotate(aMat, radians(45.0), dvec3(0, -1, 0));
	aMat = translate(aMat, dvec3(-100.0, 0.0, -140.0));
	aMat = rotate(aMat, radians(180.0), dvec3(1, 0, 0));
	glLoadMatrixd(value_ptr(aMat));
	mesh2->draw();
}
//-------------------------------------------------------------------------

Dragon::Dragon(GLuint numVert) : Entity()
{
	mesh = Mesh::generateDragon(numVert);
}

void Dragon::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINTS);
	mesh->draw();
	glLineWidth(1);
}

void Dragon::render(dmat4 const& modelViewMat) {
	dmat4 aMat = modelViewMat * modelMat;
	aMat = translate(aMat, dvec3(-40.0, -170.0, 0.0));
	aMat = scale(aMat, dvec3(40.0, 40.0, 0.0));

	Entity::render(aMat);
}
//-------------------------------------------------------------------------

Poliespiral::Poliespiral(dvec2 verIni, GLdouble angIni, GLdouble increAng,
	GLdouble ladoIni, GLdouble incrLado, GLuint numVert) : Entity()
{
	mesh = Mesh::generatePoliespiral(verIni, angIni, increAng,
		ladoIni, incrLado, numVert);
}

void Poliespiral::draw()
{
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glLineWidth(1);
}

void Poliespiral::render(dmat4 const& modelViewMat) {
	dmat4 aMat = modelViewMat * modelMat;
	aMat = scale(aMat, dvec3(10.0, 10.0, 0.0));

	Entity::render(aMat);
}
//-------------------------------------------------------------------------

RectangleTex::RectangleTex(GLdouble w, GLdouble h) : Entity()
{
	mesh = Mesh::generateRectangleTex(w, h); // con coord. de textura
	texture.load("..\\Bmps\\Zelda.bmp"); // cargamos la imagen
}

RectangleTex::RectangleTex(GLdouble w, GLdouble h, GLint numCol, GLint numFil) {
	mesh = Mesh::generateRectangleTex(w, h, numCol, numFil); // con coord. de textura
	texture.load("..\\Bmps\\Zelda.bmp"); // cargamos la imagen
}

void RectangleTex::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	texture.bind();
	mesh->draw();
	texture.unbind();
}
//-------------------------------------------------------------------------

CubeTex::CubeTex(GLdouble l) {

	mesh = Mesh::generateContCuboTex(l);
	mesh2 = Mesh::generateRectangleTex(l, l);
	// Cargamos las imagenes
	texture.load("..\\Bmps\\container.bmp");
	texture2.load("..\\Bmps\\chuches.bmp");

	modelMat = translate(modelMat, dvec3(-200.0, (l / 2) + 1.0, 0.0)); // Situa el cubo sobre "el suelo"
}

void CubeTex::draw()
{
	glCullFace(GL_FRONT);
	texture.bind();
	mesh->draw();
	texture.unbind();

	glCullFace(GL_BACK);
	texture2.bind();
	mesh->draw();
	texture2.unbind();
}

void CubeTex::drawTop()
{
	glCullFace(GL_FRONT);
	texture.bind();
	mesh2->draw();
	texture.unbind();

	glCullFace(GL_BACK);
	texture2.bind();
	mesh2->draw();
	texture2.unbind();
}

void CubeTex::render(dmat4 const& modelViewMat)
{
	glEnable(GL_CULL_FACE);

	dmat4 aMat = modelViewMat * modelMat;

	glLoadMatrixd(value_ptr(aMat));
	draw();

	aMat = modelViewMat * modelMat;

	aMat = rotate(aMat, radians(-90.0), dvec3(1, 0, 0));
	aMat = translate(aMat, dvec3(0, 0, -100.0));

	glLoadMatrixd(value_ptr(aMat));
	drawTop();

	aMat = modelViewMat * modelMat;

	aMat = rotate(aMat, radians(90.0), dvec3(1, 0, 0));
	aMat = rotate(aMat, radians(45.0), dvec3(0, -1, 0));
	aMat = translate(aMat, dvec3(-100.0, 0.0, -140.0));
	glLoadMatrixd(value_ptr(aMat));

	drawTop();

	glDisable(GL_CULL_FACE);
}

//-------------------------------------------------------------------------

TriPyramidTex::TriPyramidTex(GLdouble r, GLdouble h) : Entity()
{
	mesh = Mesh::generateTriPyramidTex(r, h);
	texture.load("..\\Bmps\\Zelda.bmp"); // cargamos la imagen
}

void TriPyramidTex::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	texture.bind();
	mesh->draw();
	texture.unbind();
}

//-------------------------------------------------------------------------

Suelo::Suelo(GLdouble w, GLdouble h, GLint repCols, GLint repFils) : Entity() {
	mesh = Mesh::generateRectangleTex(w, h, repCols, repFils);
	texture.load("..\\Bmps\\baldosaC.bmp"); // cargamos la imagen

	modelMat = rotate(modelMat, radians(90.0), dvec3(1, 0, 0)); // Define la matriz de modo que sea horizontal
}

void Suelo::draw()
{
	texture.bind();
	mesh->draw();
	texture.unbind();
}

void Suelo::render(dmat4 const& modelViewMat)
{
	glEnable(GL_REPEAT);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
	draw();
	glDisable(GL_REPEAT);
}

//-------------------------------------------------------------------------

GlassPot::GlassPot(GLdouble l) : Entity() {
	mesh = Mesh::generateContCuboTex(l);
	texture.load("..\\Bmps\\window.bmp", 150);
	modelMat = translate(modelMat, dvec3(200.0, (l / 2) + 1.0, 200.0)); // Situa el cubo sobre "el suelo"
}

void GlassPot::draw()
{
	texture.bind();
	mesh->draw();
	texture.unbind();
}

void GlassPot::render(dmat4 const& modelViewMat)
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
	draw();

	glDepthMask(GL_TRUE);
}

//-------------------------------------------------------------------------

Grass::Grass(GLdouble w, GLdouble h) : Entity() {
	mesh = Mesh::generateRectangleTex(w, h);
	texture.load("..\\Bmps\\grass.bmp", { 0,0,0 }, 0);
	modelMat = translate(modelMat, dvec3(200.0, (h / 2) + 1.0, 200.0)); // Lo situa sobre "el suelo"
	modelMat = rotate(modelMat, radians(45.0), dvec3(0, 1, 0));
}

void Grass::draw()
{
	texture.bind();
	mesh->draw();
	texture.unbind();
}

void Grass::render(dmat4 const& modelViewMat)
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Hace transparente al principio
	glDepthMask(GL_FALSE);

	dmat4 aMat = modelViewMat * modelMat;

	glLoadMatrixd(value_ptr(aMat));
	draw();

	aMat = rotate(aMat, radians(90.0), dvec3(0, 1, 0));
	glLoadMatrixd(value_ptr(aMat));
	draw();

	glDepthMask(GL_TRUE);
}

//-------------------------------------------------------------------------

Foto::Foto(GLdouble w, GLdouble h) : Entity() {
	mesh = Mesh::generateRectangleTex(w, h);
	texture.load("..\\Bmps\\renderizado.bmp"); // Esto llama al init()
	modelMat = translate(modelMat, dvec3(0.0, 2.0, 0.0));
	modelMat = rotate(modelMat, radians(90.0), dvec3(1, 0, 0)); // Define la matriz de modo que sea horizontal
}

void Foto::update(GLuint timeElapsed)
{
	timer += timeElapsed;
	if (timer > 1000)
	{
		// Esto tiene que ver con el init de textures()
		// Sin llamar al init() texture.bind() y texture.unbind() son necesarios
		texture.bind();
		texture.loadColorBuffer(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		texture.unbind();
		timer = 0;
	}
}

void Foto::draw()
{
	texture.bind();
	mesh->draw();
	texture.unbind();
}

void Foto::render(dmat4 const& modelViewMat)
{
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
	draw();
}

//-------------------------------------------------------------------------

Esfera::Esfera(GLdouble radio, GLuint meridianos, GLuint paralelos) : Entity(), radio_(radio), meridianos_(meridianos), paralelos_(paralelos)
{
	esfera = gluNewQuadric();

}

void Esfera::draw()
{
	gluQuadricDrawStyle(esfera, GLU_FILL);			// GLU_LINE, GLU_POINT
	gluQuadricNormals(esfera, GLU_SMOOTH);			// GLU_FLAT
	gluQuadricOrientation(esfera, GLU_OUTSIDE);		// GLU_INSIDE
	gluQuadricTexture(esfera, GL_TRUE);				// GLU_FALSE

	texture.bind(GL_MODULATE);
	material.load();
	gluSphere(esfera, radio_, meridianos_, paralelos_);
	texture.unbind();
}

void Esfera::render(dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
	draw();
}

//-------------------------------------------------------------------------

EsferaLuz::EsferaLuz(GLdouble radio, GLuint meridianos, GLuint paralelos) : Esfera(radio, meridianos, paralelos)
{
	esfera = gluNewQuadric();
	spotlight = new SpotLight(100.0, 0.0, 0.0, 1.0, 0.0);

	materialPeq.materialData(Material::brass);
	tex1.load("..\\Bmps\\moon.bmp");
	tex2.load("..\\Bmps\\moon.bmp");

	modelMatPeq1 = glm::translate(modelMatPeq1, glm::dvec3(-3 * (radio / 2), 200.0, 0.0));
	modelMatPeq2 = glm::translate(modelMatPeq2, glm::dvec3(3 * (radio / 2), 200.0, 0.0));

	esferaPeq1 = new Esfera(radio / 2, 100.0, 100.0);
	esferaPeq2 = new Esfera(radio / 2, 100.0, 100.0);
	esferaPeq1->setMaterial(materialPeq);
	esferaPeq2->setMaterial(materialPeq);
	esferaPeq1->setTexture(tex1);
	esferaPeq2->setTexture(tex2);
	esferaPeq1->setModelMat(modelMatPeq1);
	esferaPeq2->setModelMat(modelMatPeq2);

	ang = 0;
	tAng = 0;
	speed = 2.0;

	cx = 512;
	cy = radio * 2;
	cz = -cx;
}

void EsferaLuz::update(GLuint timeElapsed)
{
	ang = fmod(ang + speed, 360.0);
	tAng = (tAng + 0.02);
	T_ang = glm::dvec3(cx*cos(tAng), cy*sin(tAng)*sin(tAng), cz*sin(tAng)*cos(tAng));
}



void EsferaLuz::render(dmat4 const& modelViewMat)
{
	glm::dmat4 aMat = modelViewMat * modelMat;
	aMat = translate(modelViewMat, T_ang);
	aMat = rotate(aMat, radians(ang), dvec3(0, 1, 0));


	spotlight->setPos(T_ang);
	spotlight->load(aMat);

	glLoadMatrixd(value_ptr(aMat));
	draw();

	renderEsferaPeq1(aMat);
	renderEsferaPeq2(aMat);
}

void EsferaLuz::renderEsferaPeq1(glm::dmat4 const & modelViewMat)
{
	glm::dmat4 aMat = modelViewMat * modelMatPeq1;
	aMat = translate(modelViewMat, glm::dvec3(-radio_ - (radio_ / 2), 0, 0));
	glLoadMatrixd(value_ptr(aMat));
	esferaPeq1->draw();
}

void EsferaLuz::renderEsferaPeq2(glm::dmat4 const & modelViewMat)
{
	glm::dmat4 aMat = modelViewMat * modelMatPeq2;
	aMat = translate(modelViewMat, glm::dvec3(radio_ + (radio_ / 2), 0, 0));
	glLoadMatrixd(value_ptr(aMat));
	esferaPeq2->draw();
}

//-------------------------------------------------------------------------

Terreno::Terreno(std::string fileName)
{
	indexMesh = IndexMesh::generateTerrain(fileName);
}

void Terreno::render(glm::dmat4 const & modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glm::dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
	draw();
}

void Terreno::draw()
{
	texture.bind(GL_MODULATE);
	material.load();
	indexMesh->draw();
	texture.unbind();
}
