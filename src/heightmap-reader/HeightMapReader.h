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
  /**
   * Reads intensities of pixels from gray / one of rgb channel determined by step
   * @param width - width of image
   * @param height - height of image
   * @param pixels - pixels information in image
   * @param step - step that determines channel we take the intensity from
   */
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
  [[nodiscard]] unsigned getImageWidth() const;

  /**
   * Get height of image
   * @return height of image (pixel height of file)
   */
  [[nodiscard]] unsigned getImageHeight() const;

  /**
   * get intensity on queried position
   * @param x - x coordinate
   * @param y - y coordinate
   * @return intensity at [x, y]
   */
  [[nodiscard]] float getIntensityAt(unsigned x, unsigned y) const;
};
