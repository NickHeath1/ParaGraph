#pragma once
#include <GL/freeglut.h>
#include "DrawTerrain.h"

#define ASPECT_RATIO 16/9

static DrawTerrain t("terrain.bmp");

class GlutFunctions
{
public:
  GlutFunctions();
  ~GlutFunctions();

  void showInitPos();
  void reshapeFunction(int, int);
  void renderFunction();
  void display();
  void idle();
  void keyboardUp(unsigned char, int, int);
  void keyboardDown(unsigned char, int, int);
  void specialKeyboardUp(int, int, int);
  void specialKeyboardDown(int, int, int);
  void toggleParallelMode();

  void init_window(int argc, char** argv, const char* appName);
  void other_init();

  void setLight(GLfloat[], GLfloat, GLfloat, GLfloat, GLfloat);

private:
  int m_currentWidth;
  int m_currentHeight;

  int m_width;
  int m_height;

  GLfloat ambientLight[4];
  GLfloat defaultLight[4];

  int m_parallelMode;
};

void reshape(int, int);
void render();
void display();
void idle();
void onMouseMove(int x, int y);
void keyboardUp(unsigned char, int, int);
void keyboardDown(unsigned char, int, int);
void specialKeyboardUp(int, int, int);
void specialKeyboardDown(int, int, int);