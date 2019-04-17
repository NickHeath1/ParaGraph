#include <GL/glew.h>
#include "Application.h"
#include "DrawTerrain.h"

int main(int argc, char* argv[])
{
  Application a;
  a.init(argc, argv);

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboardDown);
  glutKeyboardUpFunc(keyboardUp);
  glutIdleFunc(idle);
  glutMainLoop();

  exit(EXIT_SUCCESS);
}