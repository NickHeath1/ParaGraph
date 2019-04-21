#include "DrawTerrain.h"
#include <iostream>

DrawTerrain::DrawTerrain() :
  m_terrain(nullptr)
{
}

DrawTerrain::DrawTerrain(DrawTerrain & terrain) :
  m_terrain(terrain.m_terrain)
{
}

DrawTerrain::DrawTerrain(std::string image)
{
  loadTerrain(image);
}

DrawTerrain::~DrawTerrain()
{
}

bool DrawTerrain::loadTerrain(std::string terrainImage)
{
  m_terrain = new Image(terrainImage);
  if (!m_terrain->isValid())
  {
    // TODO: log image not found
  }

  return m_terrain->isValid();
}

void DrawTerrain::draw(GLfloat sizeMult, GLfloat heightMult)
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(194.0 / 255.0, 178.0 / 255.0, 128.0 / 255.0);

  if (m_terrain->isValid())
  {
    for (int i = 0; i < m_terrain->getWidth() - 1; ++i)
    {
      for (int j = 0; j < m_terrain->getHeight() - 1; ++j)
      {
        GLfloat height00 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j).R());
        GLfloat height10 = static_cast<GLfloat>(m_terrain->getPixelAt(i + 1, j).R());
        GLfloat height01 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j + 1).R());
        GLfloat height11 = static_cast<GLfloat>(m_terrain->getPixelAt(i + 1, j + 1).R());

        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(i * sizeMult, j * sizeMult);
        glVertex3f(i * sizeMult, height00 * heightMult, j * sizeMult);
        glTexCoord2f(i * sizeMult, (j + 1) * sizeMult);
        glVertex3f(i * sizeMult, height01 * heightMult, (j + 1) * sizeMult);
        glTexCoord2f((i + 1) * sizeMult, j * sizeMult);
        glVertex3f((i + 1) * sizeMult, height10 * heightMult, j * sizeMult);

        glEnd();
      }
    }
  }
}
