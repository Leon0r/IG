﻿//#include <Windows.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
//#include <GL/glut.h>

#include <GL/freeglut.h>

#include "Camera.h"
#include "Scene.h"

#include <iostream>
using namespace std;

//---------- Global variables -------------------------------------------------------------

// Viewport position and size
Viewport viewPort(800, 600);   

// Camera position, view volume and projection
Camera camera(&viewPort);    

// Scene entities
Scene scene(&camera);   

// Textura
Texture texture;

// Coordenadas
glm::dvec2 mCoord;

// Timer
GLuint last_time_update_tick;

// Bool animacion
bool animation = true;

//----------- Callbacks ----------------------------------------------------

void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void update();
void ToggleAnimation();

//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  cout << "Starting console..." << '\n';

  // Initialization
  glutInit(&argc, argv);

  glutInitContextVersion(3, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);   
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS); 
  glutInitWindowSize(800, 600); // Window size
  // glutInitWindowPosition (140, 140);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // | GLUT_STENCIL  
  
  int win = glutCreateWindow( "Freeglut-project" ); // Window's identifier
  
  // Callback registration
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutSpecialFunc(specialKey);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutIdleFunc(update); // Se llama cuando la aplicacion esta desocupada
 
  cout << glGetString(GL_VERSION) << '\n';
  cout << glGetString(GL_VENDOR) << '\n';
 
  scene.init(); // After creating the context
   
  glutMainLoop(); 
    
  //cin.sync();   cin.get();
  glutDestroyWindow(win); // Destroy the context 

  return 0;
}
//-------------------------------------------------------------------------

void update() 
{	
	if (animation) 
	{
		scene.update(glutGet(GLUT_ELAPSED_TIME) - last_time_update_tick);
		last_time_update_tick = glutGet(GLUT_ELAPSED_TIME);
		glutPostRedisplay(); // Importante
	}
}

//-------------------------------------------------------------------------

void display() // Double buffer
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
  scene.render();   
    
  glutSwapBuffers();  
}
//-------------------------------------------------------------------------

void resize(int newWidth, int newHeight)
{
  // Resize Viewport 
  viewPort.setSize(newWidth, newHeight);  
  // Resize Scene Visible Area 
  camera.setSize(viewPort.getW(), viewPort.getH()); // Scale unchanged
}
//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case 27:  // Escape key 
    glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop 
    break;
  case '+': 
    camera.scale(+0.01); // Zoom in  
    break;
  case '-':
    camera.scale(-0.01); // Zoom out
    break;
  case 'l':
	  camera.set3D(); 
	  break;
  case 'o':
	  camera.setAZ();
	  break;
  case 'g': // Gira el diabolo
	  // scene.getDiabolo()->incrementaAngulo();
	  break;
  case 'f': // Guarda en un archivo la imagen del renderizado
	  texture.loadColorBuffer(viewPort.getW(), viewPort.getH());
	  texture.save("..\\Bmps\\renderizado.bmp");
	  break;
  case 'w':
	  camera.moveUD(10);
	  break;
  case 'a':
	  camera.moveLR(-10);
	  break;
  case 's':
	  camera.moveUD(-10);
	  break;
  case 'd':
	  camera.moveLR(10);
	  break;
  case 'q':
	  camera.moveFB(-10);
	  break;
  case 'e':
	  camera.moveFB(10);
	  break;
  case 'p':
	  camera.setPrj();
	  break;
  case 'z':
	  ToggleAnimation();
	  break;
  case 'B':
	  scene.getSpotLight()->disable();
	  break;
  case 'b':
	  scene.getSpotLight()->enable();
	  break;
  case 'N':
	  scene.getDirectionalLight()->enable();
	  break;
  case 'n':
	  scene.getDirectionalLight()->disable();
	  break;
  case 'M':
	  scene.getLightSphere()->getSpotLight()->disable();
	  break;
  case 'm':
	  scene.getLightSphere()->getSpotLight()->enable();
	  break;
  default:
    need_redisplay = false;
    break;
  } // end switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

void specialKey(int key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case GLUT_KEY_RIGHT:
    camera.pitch(1);   // rotate 1 on the X axis
    break;
  case GLUT_KEY_LEFT:
    camera.yaw(1);     // rotate 1 on the Y axis 
    break;
  case GLUT_KEY_UP:
    camera.roll(1);    // rotate 1 on the Z axis
    break;
  case GLUT_KEY_DOWN:
    camera.roll(-1);   // rotate -1 on the Z axis
    break;
  default:
    need_redisplay = false;
    break;
  } // end switch

  if (need_redisplay)
    glutPostRedisplay();
}

// Captura en mCord las coordenadas del raton invirtiendo el eje Y
void mouse(int button, int state, int x, int y)
{
	mCoord.x = x;
	mCoord.y = glutGet(GLUT_WINDOW_HEIGHT) - y;
}

// Captura las coordenadas del raton y obtiene el desplazamiento con respecto a las anteriores corrdenadas
// rota la direccion de vista de la camara en funcion del desplazamiento
void motion(int x, int y)
{
	glm::dvec2 mOffset = mCoord; // var. global
	mCoord = glm::dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
	mOffset = (mCoord - mOffset) * 0.05; // sensitivity = 0.05
	camera.rotatePY(mOffset.y, mOffset.x);
	glutPostRedisplay();
}

// Activa o desactiva la animacion de los updates
void ToggleAnimation() 
{
	animation = !animation;
}

//-------------------------------------------------------------------------