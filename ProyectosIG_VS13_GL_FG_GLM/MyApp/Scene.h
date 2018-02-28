//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <vector>
#include "Camera.h"
#include "Entities.h"

using namespace std;

//-------------------------------------------------------------------------

class Scene	
{ 
public:
    Scene(Camera* cam): camera(cam) { };
	  ~Scene();
    void init();
	  void render();
	  Diabolo* getDiabolo(){ return d; }
protected:
	  Camera* camera;
	  Diabolo* d;

	  vector<Entity*> objetos;
	  vector<pair<int, int>> pares;
	  int h, w;

	  int countElements();
	  void findNewSize();
	  void findPositions(int numElements);
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_