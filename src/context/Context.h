#pragma once

#include <vector>

#include "src/transform-stack/TransformStack.h"
#include "src/light/Light.h"
#include "src/scene.h"

class Context {
  unsigned width, height;
  std::vector<Light> lights;
  std::vector<std::vector<Color>> colorBuffer;
  TransformStack modelView;
  TransformStack projection;

  std::vector<HeightMap> heightMaps;

  struct Viewport {
    int x, y;
    float w2, h2;
  };
  Viewport viewport;

public:
  /**
   * Create context of given width and height
   * @param width - width of the context
   * @param height - height of the context
   */
  explicit Context(unsigned width, unsigned height);

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
   * Adds height map to context
   * @param heightMap
   */
  void addHeightMap(const HeightMap &heightMap);

  /**
   * Set model-view matrix to look in eye direction
   * @param center - center of the view
   * @param eye - vector where eye is looking
   * @param up - up vector
   */
  void lookAt(Point3d center, Vector3d eye, Vector3d up);

  /**
   * Get color buffer of the context
   * @return color buffer - matrix of colors
   */
  [[nodiscard]] const std::vector<std::vector<Color>> &getColorBuffer() const;

  /**
   * Ray trace scene
   */
  void rayTrace();
};