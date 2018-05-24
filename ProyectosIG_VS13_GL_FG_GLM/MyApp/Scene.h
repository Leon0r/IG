//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include <vector>
#include "Camera.h"
#include "Entities.h"
#include "Light.h"
#include "SpotLight.h"

using namespace std;

//-------------------------------------------------------------------------

class Scene
{
public:
	Scene(Camera* cam) : camera(cam), modelMat1(1.0), modelMat2(1.0), modelMat3(1.0) { };
	~Scene();
	void init();
	void render();
	void update(GLuint timeElapsed);

	SpotLight* getSpotLight() { return spotLight; }
	Light* getDirectionalLight() { return directionalLight; }
protected:
	Camera * camera;

	SpotLight* spotLight;
	Light* directionalLight;

	Esfera* entity1;
	Esfera* entity2;
	Esfera* entity3;
	EsferaLuz* lightSphere;

	Texture tex1,
			tex2,
			tex3,
			tex4;

	Material mat1,
			 mat2, 
			 mat3,
			 mat4;

	glm::dmat4 modelMat1,
		       modelMat2,
		       modelMat3,
			   modelMat4;

	vector<Entity*> objetos;
	vector<pair<int, int>> pares;
	int h, w;

	int countElements();
	void findNewSize();
	void findPositions(int numElements);
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_