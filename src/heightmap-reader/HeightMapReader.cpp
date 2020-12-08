#include "HeightMapReader.h"

void HeightMapReader::readFormat(unsigned width, unsigned height, const unsigned char *pixels, const unsigned step) {
  for (unsigned i = 0; i < width * height; ++i) {
    unsigned char v = *pixels;
    unsigned x = i / width;
    unsigned y = i % width;
    imageMatrix[x][y] = (float)v / (float)std::numeric_limits<unsigned char>::max();
    pixels += step;
  }
}

HeightMapReader::HeightMapReader(const std::string &fileName) {
  const auto fileName_c = fileName.c_str();
  corona::Image *img = corona::OpenImage(fileName_c);
  if (!img) {
    std::cerr << "invalid file" << std::endl;
    throw std::invalid_argument("received invalid file");
  }

  int width = img->getWidth();
  int height = img->getHeight();
  auto *pixels = (unsigned char *) img->getPixels();

  imageMatrix = std::vector<std::vector<float>>(height);
  for (int i = 0; i < height; i++) imageMatrix[i] = std::vector<float>(width);

  corona::PixelFormat format = img->getFormat();
  switch (format) {
    case corona::PF_I8:
      readFormat(width, height, pixels, 1);
      break;
    case corona::PF_B8G8R8:
    case corona::PF_R8G8B8:
      readFormat(width, height, pixels, 3);
      break;
    case corona::PF_B8G8R8A8:
    case corona::PF_R8G8B8A8:
      readFormat(width, height, pixels, 4);
      break;
    default:
      std::cerr << "invalid file type" << std::endl;
      throw std::invalid_argument("received invalid file type");
  }

  delete img;
}
unsigned HeightMapReader::getImageHeight() const {
  if (imageMatrix.empty()) return 0;
  return imageMatrix.size();
}

unsigned HeightMapReader::getImageWidth() const {
  return imageMatrix[0].size();
}
float HeightMapReader::getIntensityAt(unsigned row, unsigned col) const {
  if (col >= getImageWidth() || row >= getImageHeight()) {
    std::cerr << "Queried point was ouf of range" << std::endl;
    throw std::out_of_range("point out of range was queried");
  }
  return imageMatrix[row][col];
}
