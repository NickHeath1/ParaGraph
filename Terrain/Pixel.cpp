#include "Pixel.h"

Pixel::Pixel() :
  m_r(0),
  m_g(0),
  m_b(0)
{
}

Pixel::Pixel(Pixel& pixel) :
  m_r(pixel.R()),
  m_g(pixel.G()),
  m_b(pixel.B())
{
}