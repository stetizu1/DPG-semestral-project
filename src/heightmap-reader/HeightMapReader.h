#pragma once

#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>

#include <corona.h>

/**
 * Class for reading height map from file
 */
class HeightMapReader {
  std::vector<std::vector<unsigned char>> imageMatrix;
  // to read grayscale, rgb and rgba
  void readFormat(unsigned width, unsigned height, const unsigned char *pixels, unsigned step);

public:
  /**
   * Reads map from given file and stores it inside imageMap;
   * @param fileName - name of file from which can heightmap be read
   */
  explicit HeightMapReader(const std::string &fileName);

  /**
   * Get width of image
   * @return width of image (pixel width of file)
   */
  unsigned getImageWidth();

  /**
   * Get height of image
   * @return height of image (pixel height of file)
   */
  unsigned getImageHeight();

  /**
   * get intensity on queried position
   * @param x - x coordinate
   * @param y - y coordinate
   * @return intensity at [x, y]
   */
  float getIntensityAt(unsigned x, unsigned y);
};
