#pragma once
#include <GL/freeglut.h>
#include "Image.h"

class DrawTerrain
{
public:
  DrawTerrain();
  DrawTerrain(DrawTerrain& terrain);
  DrawTerrain(std::string image);

  ~DrawTerrain();

  bool loadTerrain(std::string terrainImage);
  void draw(GLfloat, GLfloat, int);

  Image *getImage() { return m_terrain; }

private:
  Image *m_terrain;
};