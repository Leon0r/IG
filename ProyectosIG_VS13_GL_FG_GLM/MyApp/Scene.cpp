#include "Scene.h"

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  
  
  camera->setAZ();
    
  // lights
  // textures  

  // objets
  /*objetos.push_back(new EjesRGB(200.0));
  objetos.push_back(new Triangle(200.0));
  objetos.push_back(new TriangleRGB(50.0)); 
  objetos.push_back(new TriPyramid(50.0, 100.0));
  objetos.push_back(new ContCubo(200.0));


  objetos.push_back(new Diabolo(100.0, 100.0));
  objetos.push_back(new Cubo(100.0));*/
  objetos.push_back(new Dragon(3000));
 //objetos.push_back(new Poliespiral({ 0, 0 }, 0, 160, 1, 1, 50));

  findPositions(countElements());
  findNewSize();
}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources 
  
  for each (Entity* it in objetos)
  {
	  delete it;
  }
}
//-------------------------------------------------------------------------

void Scene::render()
{
	glMatrixMode(GL_MODELVIEW);

	camera->getVP()->setSize(w, h);

	for (int i = 0; i < objetos.size(); i++){
		camera->getVP()->setPosition(pares[i].first, pares[i].second);

		objetos[i]->render(camera->getViewMat());
	}
}
//-------------------------------------------------------------------------

int Scene::countElements(){
	int numElements = 0;
	for each (Entity* it in objetos){
		numElements++;
	}
	return numElements;
}
//-------------------------------------------------------------------------

void Scene::findNewSize(){
	int newW, newH;

	newH = camera->getVP()->getH() / round(sqrt(countElements()));
	newW = camera->getVP()->getW() / (countElements() / round(sqrt(countElements())));

	w = newW;
	h = newH;
}

void Scene::findPositions(int numElements){
	int newW, newH, numCols, numFils;
	pares.resize(numElements);

	numFils = round(sqrt(numElements));
	numCols = (numElements / numFils);

	newH = camera->getVP()->getH() / numFils;
	newW = camera->getVP()->getW() / numCols;

	for (int i = 0; i < numElements; i++)
	{
		pares[i].first = newW *(i%numCols);
		pares[i].second = newH *(i/numFils);
	}	
}
//-------------------------------------------------------------------------

