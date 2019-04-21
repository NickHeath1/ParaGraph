#include "DisplayText.h"

DisplayText::DisplayText() :
	m_frame(0),
	m_time(0),
	m_timebase(0),
	m_framesString("0")
{
}

void DisplayText::displayFPS()
{
	++m_frame;
	m_time = glutGet(GLUT_ELAPSED_TIME);
	if (m_time - m_timebase > 1000) {
		m_framesString = std::to_string(m_frame);
		m_timebase = m_time;
		m_frame = 0;
	}
	drawText(0, glutGet(GLUT_WINDOW_HEIGHT) - 20, 0, 255, 0, "FPS: " + m_framesString);
}

void DisplayText::drawText(int xPos, int yPos, unsigned char r, unsigned char g, unsigned char b, std::string text)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

	glDisable(GL_LIGHTING);
	glColor3f((GLfloat) r / 255.0, (GLfloat) g / 255.0, (GLfloat) b / 255.0);
	glRasterPos2i(xPos, yPos);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text.c_str());

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

DisplayText::~DisplayText()
{

}