#include "DrawTerrain.h"
#include <iostream>
#include <mutex>

DrawTerrain::DrawTerrain() :
  m_terrain(nullptr)
{
}

DrawTerrain::DrawTerrain(DrawTerrain& terrain) :
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

void DrawTerrain::draw(GLfloat sizeMult, GLfloat heightMult, int parallelMode)
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(66.0 / 255.0, 158.0 / 255.0, 244.0 / 255.0);
  //glColor3f(194.0 / 255.0, 178.0 / 255.0, 128.0 / 255.0);

  unsigned int terrainWidth = m_terrain->getWidth();
  unsigned int terrainHeight = m_terrain->getHeight();

  if (m_terrain->isValid())
  {
    if (parallelMode == 0) // Serial
    {
      for (int i = 0; i < m_terrain->getWidth() - 1; ++i)
      {
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j < m_terrain->getHeight() - 1; ++j)
        {
          GLfloat height00 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j).R());
          GLfloat height10 = static_cast<GLfloat>(m_terrain->getPixelAt(i + 1, j).R());
          GLfloat height01 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j + 1).R());
          GLfloat height11 = static_cast<GLfloat>(m_terrain->getPixelAt(i + 1, j + 1).R());

          glTexCoord2f(i * sizeMult, j * sizeMult);
          glVertex3f(i * sizeMult, height00 * heightMult, j * sizeMult);
          glTexCoord2f(i * sizeMult, (j + 1) * sizeMult);
          glVertex3f(i * sizeMult, height01 * heightMult, (j + 1) * sizeMult);
          glTexCoord2f((i + 1) * sizeMult, j * sizeMult);
          glVertex3f((i + 1) * sizeMult, height10 * heightMult, j * sizeMult);
        }
        glEnd();
      }
    }
    else if (parallelMode == 1) // 1 loop parallel sections (not parallel)
    {
      for (int i = 0; i < terrainWidth - 1; ++i)
      {
        // section up the last bit into fourths
        unsigned int newWidth = terrainHeight / 4;
        //#pragma omp parallel
        {
          //#pragma omp sections
          {
            //#pragma omp section
            {
              for (int j = 0; j < (float)terrainHeight / 4.0 - 1; ++j)
              {
                glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f(i * sizeMult, j * sizeMult);
                GLfloat height00 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j).R());
                glVertex3f(i * sizeMult, height00 * heightMult, j * sizeMult);

                glTexCoord2f((i + 1) * sizeMult, j * sizeMult);
                GLfloat height10 = static_cast<GLfloat>(m_terrain->getPixelAt(i + 1, j).R());
                glVertex3f((i + 1) * sizeMult, height10 * heightMult, j * sizeMult);

                glTexCoord2f(i * sizeMult, (j + 1) * sizeMult);
                GLfloat height01 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j + 1).R());
                glVertex3f(i * sizeMult, height01 * heightMult, (j + 1) * sizeMult);
                glEnd();
              }
            }

            //#pragma omp section
            {
              for (int j = (float)terrainHeight / 4.0; j < (float)terrainHeight / 2.0 - 1; ++j)
              {
                glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f(i * sizeMult, j * sizeMult);
                GLfloat height00 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j).R());
                glVertex3f(i * sizeMult, height00 * heightMult, j * sizeMult);

                glTexCoord2f((i + 1) * sizeMult, j * sizeMult);
                GLfloat height10 = static_cast<GLfloat>(m_terrain->getPixelAt(i + 1, j).R());
                glVertex3f((i + 1) * sizeMult, height10 * heightMult, j * sizeMult);

                glTexCoord2f(i * sizeMult, (j + 1) * sizeMult);
                GLfloat height01 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j + 1).R());
                glVertex3f(i * sizeMult, height01 * heightMult, (j + 1) * sizeMult);
                glEnd();
              }
            }

            //#pragma omp section
            {
              for (int j = (float)terrainHeight / 2; j < (float)terrainHeight * (3.0 / 4.0) - 1; ++j)
              {
                glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f(i * sizeMult, j * sizeMult);
                GLfloat height00 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j).R());
                glVertex3f(i * sizeMult, height00 * heightMult, j * sizeMult);

                glTexCoord2f((i + 1) * sizeMult, j * sizeMult);
                GLfloat height10 = static_cast<GLfloat>(m_terrain->getPixelAt(i + 1, j).R());
                glVertex3f((i + 1) * sizeMult, height10 * heightMult, j * sizeMult);

                glTexCoord2f(i * sizeMult, (j + 1) * sizeMult);
                GLfloat height01 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j + 1).R());
                glVertex3f(i * sizeMult, height01 * heightMult, (j + 1) * sizeMult);
                glEnd();
              }
            }

            //#pragma omp section
            {
              for (int j = (float)terrainHeight * (3.0 / 4.0); j < terrainHeight - 1; ++j)
              {

                glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f(i * sizeMult, j * sizeMult);
                GLfloat height00 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j).R());
                glVertex3f(i * sizeMult, height00 * heightMult, j * sizeMult);

                glTexCoord2f((i + 1) * sizeMult, j * sizeMult);
                GLfloat height10 = static_cast<GLfloat>(m_terrain->getPixelAt(i + 1, j).R());
                glVertex3f((i + 1) * sizeMult, height10 * heightMult, j * sizeMult);

                glTexCoord2f(i * sizeMult, (j + 1) * sizeMult);
                GLfloat height01 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j + 1).R());
                glVertex3f(i * sizeMult, height01 * heightMult, (j + 1) * sizeMult);
                glEnd();
              }
            }
          }
          //#pragma omp barrier
        }
      }
    }
    else if (parallelMode == 2) // 2 loop parallel sections
    {
      for (int i = 0; i < terrainWidth - 1; ++i)
      {
        // section up the last bit into fourths
        unsigned int newWidth = terrainHeight / 4;
#pragma omp parallel
        {
#pragma omp sections
          {
#pragma omp section
            {
              for (int j = 0; j < (float)terrainHeight / 4.0 - 1; ++j)
              {
                glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f(i * sizeMult, j * sizeMult);
                GLfloat height00 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j).R());
                glVertex3f(i * sizeMult, height00 * heightMult, j * sizeMult);

                glTexCoord2f((i + 1) * sizeMult, j * sizeMult);
                GLfloat height10 = static_cast<GLfloat>(m_terrain->getPixelAt(i + 1, j).R());
                glVertex3f((i + 1) * sizeMult, height10 * heightMult, j * sizeMult);

                glTexCoord2f(i * sizeMult, (j + 1) * sizeMult);
                GLfloat height01 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j + 1).R());
                glVertex3f(i * sizeMult, height01 * heightMult, (j + 1) * sizeMult);
                glEnd();
              }
            }

#pragma omp section
            {
              for (int j = (float)terrainHeight / 4.0; j < (float)terrainHeight / 2.0 - 1; ++j)
              {
                glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f(i * sizeMult, j * sizeMult);
                GLfloat height00 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j).R());
                glVertex3f(i * sizeMult, height00 * heightMult, j * sizeMult);

                glTexCoord2f((i + 1) * sizeMult, j * sizeMult);
                GLfloat height10 = static_cast<GLfloat>(m_terrain->getPixelAt(i + 1, j).R());
                glVertex3f((i + 1) * sizeMult, height10 * heightMult, j * sizeMult);

                glTexCoord2f(i * sizeMult, (j + 1) * sizeMult);
                GLfloat height01 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j + 1).R());
                glVertex3f(i * sizeMult, height01 * heightMult, (j + 1) * sizeMult);
                glEnd();
              }
            }

#pragma omp section
            {
              for (int j = (float)terrainHeight / 2; j < (float)terrainHeight * (3.0 / 4.0) - 1; ++j)
              {
                glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f(i * sizeMult, j * sizeMult);
                GLfloat height00 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j).R());
                glVertex3f(i * sizeMult, height00 * heightMult, j * sizeMult);

                glTexCoord2f((i + 1) * sizeMult, j * sizeMult);
                GLfloat height10 = static_cast<GLfloat>(m_terrain->getPixelAt(i + 1, j).R());
                glVertex3f((i + 1) * sizeMult, height10 * heightMult, j * sizeMult);

                glTexCoord2f(i * sizeMult, (j + 1) * sizeMult);
                GLfloat height01 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j + 1).R());
                glVertex3f(i * sizeMult, height01 * heightMult, (j + 1) * sizeMult);
                glEnd();
              }
            }

#pragma omp section
            {
              for (int j = (float)terrainHeight * (3.0 / 4.0); j < terrainHeight - 1; ++j)
              {

                glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f(i * sizeMult, j * sizeMult);
                GLfloat height00 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j).R());
                glVertex3f(i * sizeMult, height00 * heightMult, j * sizeMult);

                glTexCoord2f((i + 1) * sizeMult, j * sizeMult);
                GLfloat height10 = static_cast<GLfloat>(m_terrain->getPixelAt(i + 1, j).R());
                glVertex3f((i + 1) * sizeMult, height10 * heightMult, j * sizeMult);

                glTexCoord2f(i * sizeMult, (j + 1) * sizeMult);
                GLfloat height01 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j + 1).R());
                glVertex3f(i * sizeMult, height01 * heightMult, (j + 1) * sizeMult);
                glEnd();
              }
            }
          }
        }
      }
    }
    else if (parallelMode == 3) // 3 loop parallel for inner loop
    {
#pragma omp parallel for
      for (int i = 0; i < m_terrain->getWidth() - 1; ++i)
      {
        glBegin(GL_TRIANGLE_STRIP);
        //#pragma omp parallel for
        for (int j = 0; j < m_terrain->getHeight() - 1; ++j)
        {
          GLfloat height00 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j).R());
          GLfloat height10 = static_cast<GLfloat>(m_terrain->getPixelAt(i + 1, j).R());
          GLfloat height01 = static_cast<GLfloat>(m_terrain->getPixelAt(i, j + 1).R());
          GLfloat height11 = static_cast<GLfloat>(m_terrain->getPixelAt(i + 1, j + 1).R());

          glTexCoord2f(i * sizeMult, j * sizeMult);
          glVertex3f(i * sizeMult, height00 * heightMult, j * sizeMult);
          glTexCoord2f(i * sizeMult, (j + 1) * sizeMult);
          glVertex3f(i * sizeMult, height01 * heightMult, (j + 1) * sizeMult);
          glTexCoord2f((i + 1) * sizeMult, j * sizeMult);
          glVertex3f((i + 1) * sizeMult, height10 * heightMult, j * sizeMult);
        }
        glEnd();
      }
    }
    else if (parallelMode == 4) // serial spheres
    {
      for (int i = 0; i < m_terrain->getWidth() - 1; ++i)
      {
        //#pragma omp parallel for
        for (int j = 0; j < m_terrain->getHeight() - 1; ++j)
        {
          glPushMatrix();
          glTranslatef(i * sizeMult, m_terrain->getPixelAt(i, j).R() * heightMult, j * sizeMult);
          glutWireSphere(1, 2, 2);
          glPopMatrix();
        }
      }
    }
    else if (parallelMode == 5) // parallel spheres
    {
      for (int i = 0; i < m_terrain->getWidth() - 1; ++i)
      {
        #pragma omp parallel for
        for (int j = 0; j < m_terrain->getHeight() - 1; ++j)
        {
          glPushMatrix();
          glTranslatef(i * sizeMult, m_terrain->getPixelAt(i, j).R() * heightMult, j * sizeMult);
          glutWireSphere(1, 2, 2);
          glPopMatrix();
        }
      }
    }
  }
}