#include "Application.h"

static const char* APP_NAME = "Terrain Test";

Application::Application() :
	m_appName((char*)APP_NAME),
	m_windowHandle(0),
  m_glut(GlutFunctions())
{
} // Ctor

Application::~Application()
{
} // Dtor

void Application::init(int argc, char* argv[])
{
  m_glut.init_window(argc, argv, m_appName);
  m_glut.other_init();
} // init