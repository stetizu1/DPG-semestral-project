#pragma once

#include <vector>
#include <numbers>

#include "src/helper-types/Viewport.h"
#include "src/light/Light.h"
#include "src/scene.h"
#include "src/transform-stack/TransformStack.h"

/**
 * Context storage
 *
 * Stores basic model and view data as color buffer for the image
 * Provides operation for rendering (lookAt, raytrace) and getting context data
 */
class Context {
  const unsigned width, height;
  std::vector<Light> lights;
  std::vector<std::vector<Color>> colorBuffer;
  TransformStack modelView;
  TransformStack projection;
  Color bgColor;

  const HeightMap *heightMap;

  Viewport viewport;

public:
  /**
   * Create context of given width and height with given height map
   * @param width - width of the context
   * @param height - height of the context
   * @param heightMap - heightmap that should be rendered
   * @param bgColor - color of the background
   */
  explicit Context(unsigned int width, unsigned int height, const HeightMap *heightMap, const Color &bgColor);

  /**
   * Create context with default width and height (in scene.h)
   */
  explicit Context();

  /**
   * Get lights in context
   * @return lights in the context
   */
  [[nodiscard]] const std::vector<Light> &getLights() const;

  /**
   * Get color buffer of the context
   * @return color buffer - matrix of colors
   */
  [[nodiscard]] const std::vector<std::vector<Color>> &getColorBuffer() const;

  /**
   * Get Context width
   * @return width of the context
   */
  [[nodiscard]] unsigned getWidth() const;

  /**
   * Get context height
   * @return height of the context
   */
  [[nodiscard]] unsigned getHeight() const;

  /**
   * Get color for background
   * @return background color
   */
  [[nodiscard]] const Color &getBgColor() const;

  /**
   * Get height map in the context
   * @return
   */
  [[nodiscard]] const HeightMap *getHeightMap() const;

  void setToColorBuffer(unsigned x, unsigned y, const Color &color);

  /**
   * Set model-view matrix to look in eye direction
   * @param center - center of the view
   * @param eye - vector where eye is looking
   * @param up - up vector
   */
  void lookAt(Point3d center, Vector3d eye, Vector3d up);

  /**
   * Ray trace scene
   */
  void rayTrace();
};