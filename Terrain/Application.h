#pragma once
#include "GlutFunctions.h"

#include <GL/freeglut.h>

#include <stdio.h>
#include <string>
#include <stdlib.h>

class Application 
{
public:
  Application();
  ~Application();
  void init(int, char*[]);

private:
  char*	          m_appName;
  int             m_windowHandle;
  GlutFunctions   m_glut;
};