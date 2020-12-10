#include "scene.h"


const std::vector<Light> scene::lights = {
  Light(Point3d(275, 549, 295))
};

const std::vector<Material> scene::materials = {
  Material(Color(0.2, 0.8, 0.2), 1, 0, 0)
};

const std::vector<HeightMap> scene::heightMaps = {
  HeightMap(HeightMapReader("../data/world.jpg"), 200, 200, 200, materials[0])
};

