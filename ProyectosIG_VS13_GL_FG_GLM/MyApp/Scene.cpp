#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SMOOTH);

	camera->setAZ();

	// LIGHTS
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);

	directionalLight = new Light();
	spotLight = new SpotLight(20.0, 0.0, 1.0, 0.0, 0);

	// TEXTURES  
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	// OBJECTS

	// PRACTICA 1 \\

	// objetos.push_back(new Foto(80, 60));
	// objetos.push_back(new EjesRGB(200.0));
	// objetos.push_back(new Triangle(200.0));
	// objetos.push_back(new RectangleTex(300, 300, 3, 2));
	// objetos.push_back(new CubeTex(200));
	// objetos.push_back(new TriangleRGB(200.0)); 
	// objetos.push_back(new TriPyramid(200.0, 200.0));
	// objetos.push_back(new ContCubo(200.0));
	// objetos.push_back(new Cubo(200.0));
	/*modelMat = rotate(modelMat, radians(90.0), dvec3(1, 0, 0));
	e = new Diabolo(100.0, 200.0);
	e->setModelMat(modelMat);
	objetos.push_back(e);*/
	// objetos.push_back(new Dragon(3000));
	// objetos.push_back(new TriPyramidTex(200.0, 200.0));
	// objetos.push_back(new Poliespiral({ 0, 0 }, 0, 89.5, 0.5, 0.5, 100));
	// objetos.push_back(new Suelo(800, 800, 8, 8));
	// objetos.push_back(new Grass(200, 200));
	// objetos.push_back(new GlassPot(200));
	// findPositions(countElements());
	// findNewSize();

	// PRACTICA 2 \\

	modelMat1 = translate(modelMat1, dvec3(0.0, 30.0, 0.0));
	mat1.materialData(Material::brass);
	tex1.load("..\\Bmps\\venus.bmp");
	modelMat2 = translate(modelMat2, dvec3(200.0, 150.0, 0.0));
	mat2.materialData(Material::brass);
	tex2.load("..\\Bmps\\moon.bmp");
	modelMat3 = translate(modelMat3, dvec3(-150.0, 100.0, 0.0));
	mat3.materialData(Material::brass);
	tex3.load("..\\Bmps\\sun.bmp");
	modelMat4 = translate(modelMat4, dvec3(0.0, -500.0, 0.0));
	mat4.materialData(Material::brass);
	tex4.load("..\\Bmps\\sun.bmp");
	modelMat5 = translate(modelMat5, glm::dvec3(-200.0, -200.0, -100.0));
	mat5.materialData(Material::brass);

	entity1 = new Esfera(50, 20, 20);
	entity1->setModelMat(modelMat1);
	entity1->setTexture(tex1);
	entity1->setMaterial(mat1);
	objetos.push_back(entity1);

	entity2 = new Esfera(80, 20, 20);
	entity2->setModelMat(modelMat2);
	entity2->setTexture(tex2);
	entity2->setMaterial(mat2);
	objetos.push_back(entity2);

	entity3 = new Esfera(40, 30, 30);
	entity3->setModelMat(modelMat3);
	entity3->setTexture(tex3);
	entity3->setMaterial(mat3);
	objetos.push_back(entity3);

	lightSphere = new EsferaLuz(90, 30, 30);
	lightSphere->setModelMat(modelMat4);
	lightSphere->setTexture(tex4);
	lightSphere->setMaterial(mat4);
	objetos.push_back(lightSphere);

	terreno = new Terreno("..\\Bmps\\terrain.raw");
	terreno->setTexture(tex5);
	terreno->setMaterial(mat5);
	terreno->setModelMat(modelMat5);
	objetos.push_back(terreno);
}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources 

	for each (Entity* it in objetos)
	{
		delete it;
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
//-------------------------------------------------------------------------

void Scene::render()
{
	glMatrixMode(GL_MODELVIEW);

	// Cargar luces
	directionalLight->load(camera->getViewMat());

	spotLight->setPosPos(camera->getPosition());
	spotLight->setDirection(camera->getFront().x, camera->getFront().y, camera->getFront().z);
	spotLight->load(camera->getViewMat());

	// camera->getVP()->setSize(w, h);

	for (int i = 0; i < objetos.size(); i++) {
		// camera->getVP()->setPosition(pares[i].first, pares[i].second);
		camera->getVP()->setPosition(0, 0);
		objetos[i]->render(camera->getViewMat());
	}
}

void Scene::update(GLuint timeElapsed)
{
	for each (Entity* it in objetos) {
		it->update(timeElapsed);
	}
}

//-------------------------------------------------------------------------

int Scene::countElements() {
	int numElements = 0;
	for each (Entity* it in objetos) {
		numElements++;
	}
	return numElements;
}
//-------------------------------------------------------------------------

void Scene::findNewSize() {
	int newW, newH;

	newH = camera->getVP()->getH() / round(sqrt(countElements()));
	newW = camera->getVP()->getW() / (countElements() / round(sqrt(countElements())));

	w = newW;
	h = newH;
}
//-------------------------------------------------------------------------

void Scene::findPositions(int numElements) {
	int newW, newH, numCols, numFils;
	pares.resize(numElements);

	numFils = round(sqrt(numElements));
	numCols = (numElements / numFils);

	newH = camera->getVP()->getH() / numFils;
	newW = camera->getVP()->getW() / numCols;

	for (int i = 0; i < numElements; i++)
	{
		pares[i].first = newW * (i%numCols);
		pares[i].second = newH * (i / numFils);
	}
}
//-------------------------------------------------------------------------

