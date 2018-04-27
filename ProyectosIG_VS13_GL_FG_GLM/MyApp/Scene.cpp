#include "Scene.h"

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  
  
  camera->setAZ();
    
  // LIGHTS
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);

  // TEXTURES  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);

  // OBJECTS
  objetos.push_back(new Foto(80, 60));

  objetos.push_back(new EjesRGB(200.0));
  //objetos.push_back(new Triangle(200.0));
  
  // objetos.push_back(new RectangleTex(300, 300, 3, 2));
  objetos.push_back(new CubeTex(200));

  // objetos.push_back(new TriangleRGB(200.0)); 
  // objetos.push_back(new TriPyramid(200.0, 200.0));
  // objetos.push_back(new ContCubo(200.0));
  // objetos.push_back(new Cubo(200.0));

   d = new Diabolo(100.0, 200.0);
   objetos.push_back(d);  

  // objetos.push_back(new Dragon(3000));
  // objetos.push_back(new TriPyramidTex(200.0, 200.0));
  // objetos.push_back(new Poliespiral({ 0, 0 }, 0, 89.5, 0.5, 0.5, 100));

  objetos.push_back(new Suelo(800, 800, 8, 8));


  objetos.push_back(new Grass(200, 200));

  objetos.push_back(new GlassPot(200));

  // findPositions(countElements());
  // findNewSize();
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
	
	// camera->getVP()->setSize(w, h);

	for (int i = 0; i < objetos.size(); i++){
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
//-------------------------------------------------------------------------

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

