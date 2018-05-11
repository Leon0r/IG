//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include <vector>
#include "Camera.h"
#include "Entities.h"
#include "SpotLight.h"

using namespace std;

//-------------------------------------------------------------------------

class Scene
{
public:
	Scene(Camera* cam) : camera(cam), modelMat(1.0) { };
	~Scene();
	void init();
	void render();
	void update(GLuint timeElapsed);
protected:
	Camera * camera;
	Entity* e;
	Light* light;

	glm::dmat4 modelMat;
	vector<Entity*> objetos;
	vector<pair<int, int>> pares;
	int h, w;

	int countElements();
	void findNewSize();
	void findPositions(int numElements);
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_