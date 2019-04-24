#include "GlutFunctions.h"
#include <ctime>
#include <iostream>
#include <omp.h>

#define NUM_PARALLEL_MODES 7
#define MIN_NUM_THREADS 1
#define MAX_NUM_THREADS 64

// IMPORTANT NOTES:
// ----------------
// X: WIDTH
// Z: HEIGHT
// ----------------

// ----- Static vars ---------------------------------------
/// ---- Heightmap -----------------------------------------
static int heightMult = 3420;
static int widthMult = 285;

/// ---- Animation -----------------------------------------

static bool m_animated = false;
static int m_forward = 1;

static bool m_increaseHeight = false;
static bool m_decreaseHeight = false;

static bool m_increaseWidth = false;
static bool m_decreaseWidth = false;

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
	m_parallelMode(0), m_numThreads(1)
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
  omp_set_num_threads(1);
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

  if (m_increaseHeight) { heightMult += 20; }
  if (m_decreaseHeight) { heightMult -= 20; }

  if (m_increaseWidth) { widthMult += 1; }
  if (m_decreaseWidth) { widthMult -= 1; }

  t.draw(widthMult, heightMult, m_parallelMode);
  textDraw.displayFPS();
  textDraw.displayParallelMode(m_parallelMode);
  textDraw.displayThreadCount(m_numThreads);

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
  case '-':
	  if (m_numThreads > MIN_NUM_THREADS)
	  {
		  --m_numThreads;
		  omp_set_num_threads(m_numThreads);
	  }
	  break;
  case '+':
  case '=':
	  if (m_numThreads < MAX_NUM_THREADS)
	  {
		  ++m_numThreads;
		  omp_set_num_threads(m_numThreads);
	  }
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
  case GLUT_KEY_UP:
    m_increaseHeight = false;
    break;
  case GLUT_KEY_DOWN:
    m_decreaseHeight = false;
    break;
  case GLUT_KEY_LEFT:
    m_decreaseWidth = false;
    break;
  case GLUT_KEY_RIGHT:
    m_increaseWidth = false;
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
  case GLUT_KEY_UP:
    m_increaseHeight = true;
    break;
  case GLUT_KEY_DOWN:
    m_decreaseHeight = true;
    break;
  case GLUT_KEY_LEFT:
    m_decreaseWidth = true;
    break;
  case GLUT_KEY_RIGHT:
    m_increaseWidth = true;
    break;
  }
}

void GlutFunctions::showInitPos()
{
  // Default position is looking in -z. The image is drawn in the +x, +z region.
  // Rotate such that we are looking in that direction
  glRotatef(180.0, 1, 0, 0);
  glRotatef(20.0, 1, 0, 0);

  // Translate to the height of the heightmap where we currently are (0, 0);
  glTranslatef(0, -(t.getImage()->getPixelAt(0,0).R() * heightMult) + 5000, 0);
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