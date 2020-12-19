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
class MapReader {
  std::vector<std::vector<float>> imageMatrix;
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
  explicit MapReader(const std::string &fileName);

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
   * @param row - row
   * @param col - column
   * @return intensity at position
   */
  [[nodiscard]] float getIntensityAt(unsigned row, unsigned col) const;
};
