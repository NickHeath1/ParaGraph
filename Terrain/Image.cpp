#include "Image.h"

Image::Image() :
  m_height(0),
  m_width(0),
  m_valid(false),
  m_pixArr(nullptr)
{
}

Image::Image(Image &image) :
  m_height(image.m_height),
  m_width(image.m_width),
  m_valid(image.m_valid),
  m_pixArr(image.m_pixArr)
{
}

Image::Image(std::string filename) :
  m_height(0),
  m_width(0),
  m_pixArr(nullptr),
  m_valid(false)
{
  switch (getImageType(filename))
  {
  case ImageType::BMP:
    loadBmp(filename);
    break;
  case ImageType::JPEG:
  case ImageType::PNG:
  case ImageType::InvalidType:
  default:
    // TODO: Error log for unhandled type here
    break;
  } 
}

std::string Image::getExtenstion(std::string filename)
{
  std::string ext = "";

  int i = filename.length() - 1;
  for (i; i > 0; --i)
  {
    if (filename[i] == '.')
    {
      if (i + 1 < filename.length() - 1)
      {
        ext = filename.substr(i + 1);
        break;
      }
    }
  }

  return ext;
}

ImageType Image::getImageType(std::string filename)
{
  ImageType type = InvalidType;
  auto file = fopen(filename.c_str(), "rb");
  if (file)
  {
    auto ext = getExtenstion(filename);
    if (ext == "bmp")
    {
      type = ImageType::BMP;
    }

    fclose(file);
  }

  return type;
}

Image::~Image()
{
  if (m_valid)
  {
    for (int i = 0; i < m_height; ++i)
    {
      delete[] m_pixArr[i];
    }

    delete[] m_pixArr;
  }
}

bool Image::loadBmp(std::string filename)
{
  if (FILE *file = fopen(filename.c_str(), "rb"))
  {
    // Allocate the memory
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    unsigned char* buffer = new unsigned char[size];
    rewind(file);

    // Get the file contents
    fread(buffer, sizeof(unsigned char), size, file);

    // Get the width and height
    for (int i = 0; i < NUM_WIDTH_BITS; ++i)
    {
      m_width |= buffer[IMAGE_WIDTH_OFFSET + i] << (8 * i);
      m_height |= buffer[IMAGE_HEIGHT_OFFSET + i] << (8 * i);
    }

    // Allocate the pixel array memory
    m_pixArr = new Pixel*[m_width];
    for (int i = 0; i < m_width; ++i)
    {
      m_pixArr[i] = new Pixel[m_height];
    }

    // Get the row padding, rows are multiples of 4 bytes
    int padding = 4 - (m_width % 4);
    if (padding == 4) padding = 0;

    // Fill the pixel array with data
    for (int i = 0; i < m_height; ++i)
    {
      for (int j = 0; j < m_width * 3; j+=3)
      {
        // Calculate the offset of the current row
        int offset = HEADER_SIZE +        // header offset
          (i * (m_width * 3 + padding)) + // vertical position (row)
          j;                              // horizontal position (column)
        
        // components are stored in the order B, G, R
        m_pixArr[j / 3][i].setB(static_cast<float>(buffer[offset]) / 255.0);
        m_pixArr[j / 3][i].setG(static_cast<float>(buffer[offset + 1]) / 255.0);
        m_pixArr[j / 3][i].setR(static_cast<float>(buffer[offset + 2]) / 255.0);
      }
    }

    m_valid = true;
  }

  return m_valid;
}

bool Image::isValid()
{
  return m_valid;
}

unsigned int Image::getHeight()
{
  return m_height;
}

unsigned int Image::getWidth()
{
  return m_width;
}

Pixel Image::getPixelAt(int x, int y)
{
  return m_pixArr[x][y];
}
