#pragma once
#include "Pixel.h"
#include <string>

#define HEADER_SIZE 0x36

#define IMAGE_WIDTH_OFFSET 0x12
#define IMAGE_HEIGHT_OFFSET 0x16
#define IMAGE_BITS_PER_PIXEL_OFFSET 0x1C

#define NUM_HEIGHT_BITS 0x4
#define NUM_WIDTH_BITS 0x4
#define NUM_BITS_PER_PIXEL 0x2

enum ImageType
{
  InvalidType = -1,
  BMP,
  JPEG,
  PNG
};

class Image
{
public:
  Image();
  Image(Image &image);
  Image(std::string filename);

  ~Image();

  std::string getExtenstion(std::string filename);
  ImageType getImageType(std::string filename);
  bool loadBmp(std::string filename);

  Pixel getPixelAt(int x, int y);
  unsigned int getHeight();
  unsigned int getWidth();
  bool isValid();

private:
  Pixel**       m_pixArr;
  unsigned int  m_height;
  unsigned int  m_width;
  bool          m_valid;
};