#include "GlutFunctions.h"
#include <ctime>
#include <iostream>

#define NUM_PARALLEL_MODES 3

// IMPORTANT NOTES:
// ----------------
// X: WIDTH
// Z: HEIGHT
// ----------------

// ----- Static vars ---------------------------------------
/// ---- Heightmap -----------------------------------------
static int heightMult = 200;
static int widthMult = 20;

/// ---- Animation -----------------------------------------

static bool m_animated = false;
static int m_forward = 1;
static double angle = 0;

static int prevX = -1, prevY = -1;

/// ---- Debug ---------------------------------------------
static auto start_time = time(0);
static int count = 0;

///
static DisplayText textDraw = DisplayText();
static GlutFunctions GF = GlutFunctions();
// ---------------------------------------------------------

GlutFunctions::GlutFunctions() :
  m_parallelMode(0)
{
  setLight(ambientLight, 0.6, 0.6, 0.6, 1);
  setLight(defaultLight, 0, 0, 0, 1); 
}

GlutFunctions::~GlutFunctions()
{
}

void GlutFunctions::setLight(GLfloat arr[], GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
  arr[0] = r;
  arr[1] = g;
  arr[2] = b;
  arr[3] = a;
}

void GlutFunctions::init_window(int argc, char** argv, const char* appName)
{
  glutInit(&argc, argv);
  m_currentWidth = glutGet(GLUT_SCREEN_WIDTH);
  m_currentHeight = glutGet(GLUT_SCREEN_HEIGHT);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(m_currentWidth, m_currentHeight);
  glutInitWindowPosition(0, 0);
  glutCreateWindow(appName);
}

void GlutFunctions::other_init()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Set background color

  // init viewport
  glutReshapeFunc(reshape);
  glutDisplayFunc(render);
}

void GlutFunctions::idle()
{
  if (m_animated) angle -= m_forward * 0.3;
  display();
}

void GlutFunctions::reshapeFunction(int width, int height)
{
  if (width == 0 || height == 0) return;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(39.0, (GLdouble)width / (GLdouble)height, 0.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glViewport(0, 0, width, height);
}

void GlutFunctions::renderFunction(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutSwapBuffers();
  glutPostRedisplay();
}

void GlutFunctions::display()
{
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  showInitPos();
  glRotatef(angle, 0, 1, 0);

  t.draw(widthMult, heightMult, m_parallelMode);
  textDraw.displayFPS();
  textDraw.displayParallelMode(m_parallelMode);

  glFlush();
  glutSwapBuffers();
}

void GlutFunctions::keyboardUp(unsigned char key, int x, int y)
{
  switch (tolower(key))
  {
  case ' ':
    m_animated = false;
    break;
  case 'w':

    break;
  case 'a':

    break;
  case 's':

    break;
  case 'd':

    break;
  }
}

void GlutFunctions::keyboardDown(unsigned char key, int, int)
{
  switch (tolower(key))
  {
  case ' ':
    m_animated = true;
    break;
  case 'w':

    break;
  case 'a':
    
    break;
  case 's':
    
    break;
  case 'd':
    
    break;
  case 'p':
    toggleParallelMode();
    break;
  }
}

void GlutFunctions::toggleParallelMode()
{
  m_parallelMode = (m_forward == 1) ?
    ++m_parallelMode % NUM_PARALLEL_MODES :
    (m_parallelMode + NUM_PARALLEL_MODES - 1) % NUM_PARALLEL_MODES;

  // TODO: display mode text
}

void GlutFunctions::specialKeyboardUp(int key, int, int)
{
  switch (key)
  {
  case GLUT_KEY_SHIFT_L:
    m_forward *= -1;
    break;
  }
}

void GlutFunctions::specialKeyboardDown(int key, int, int)
{
  switch (key)
  {
  case GLUT_KEY_SHIFT_L:
    m_forward *= -1;
    break;
  }
}

void GlutFunctions::showInitPos()
{
  // Default position is looking in -z. The image is drawn in the +x, +z region.
  // Rotate such that we are looking in that direction
  glRotatef(180.0, 1, 0, 0);
  glRotatef(5.0, 1, 0, 0);

  // Translate to the height of the heightmap where we currently are (0, 0);
  glTranslatef(0, -(t.getImage()->getPixelAt(0,0).R() * heightMult) +2000, 0);
}

// -----------------------------------------------------
// -------------- Callback Functions -------------------
// -----------------------------------------------------

void onMouseMove(int x, int y)
{
  glutWarpPointer(glutGet(GLUT_SCREEN_WIDTH) / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2);

  if (prevX == -1 || prevY == -1) { prevX = x; prevY = y; return; }
  int deltaX = static_cast<float>(x - prevX) / 1080.0 * 360.0;
  int deltaY = static_cast<float>(y - prevY) / 1080.0 * 360.0;

  glRotatef(deltaX, 0, 1, 0);
}

void reshape(int width, int height)
{
  GF.reshapeFunction(width, height);
}

void render()
{
  GF.renderFunction();
}

void display()
{
  GF.display();
}

void idle()
{
  GF.idle();
}

void keyboardUp(unsigned char key, int x, int y)
{
  GF.keyboardUp(key, x, y);
}

void keyboardDown(unsigned char key, int x, int y)
{
  GF.keyboardDown(key, x, y);
}

void specialKeyboardUp(int key, int x, int y)
{
  GF.specialKeyboardUp(key, x, y);
}

void specialKeyboardDown(int key, int x, int y)
{
  GF.specialKeyboardDown(key, x, y);
}