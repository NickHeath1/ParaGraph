#pragma once

class Pixel
{
public:
  Pixel();
  Pixel(Pixel& pixel);

  void setR(float R) { m_r = R; }
  void setG(float G) { m_g = G; }
  void setB(float B) { m_b = B; }

  float R() { return m_r; }
  float G() { return m_g; }
  float B() { return m_b; }

private:
  float m_r;
  float m_g;
  float m_b;
};