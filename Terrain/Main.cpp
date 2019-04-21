#include <GL/glew.h>
#include "Application.h"
#include "DrawTerrain.h"
#include "DisplayText.h"

int main(int argc, char* argv[])
{
  Application a;
  a.init(argc, argv);

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboardDown);
  glutKeyboardUpFunc(keyboardUp);
  glutSpecialFunc(specialKeyboardDown);
  glutSpecialUpFunc(specialKeyboardUp);
  glutIdleFunc(idle);
  glutMainLoop();

  exit(EXIT_SUCCESS);
}