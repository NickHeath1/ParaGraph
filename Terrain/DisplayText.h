#pragma once
#include <GL/freeglut.h>
#include <string>

class DisplayText {
public:
	DisplayText();

	~DisplayText();

	void displayFPS();
  void displayParallelMode(int parallelMode);
  void displayThreadCount(int numThreads);

	void drawText(int xPos, int yPos, unsigned char r, unsigned char g, unsigned char b, std::string text);

private:
	std::string m_framesString;
	int m_frame;
	int m_time;
	int m_timebase;
};
