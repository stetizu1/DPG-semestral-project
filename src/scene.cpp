#include "scene.h"


const Point3d scene::defaultCenter = Point3d(275.f, 275.f, 0.f);

const Vector3d scene::defaultEye = Vector3d(275.f, 275.f, -800.f);

const Vector3d scene::defaultUp = Vector3d(0.f, 1.f, 0.f);

const Color scene::defaultBgColor = Color(0.05f, 0.05f, 0.05f);

const std::vector<Light> scene::lights = {
  Light(Point3d(275, 549, 295))
};

const std::vector<Material> scene::materials = {
  Material(Color(0.2, 0.8, 0.2), 1, 0, 0)
};

const std::vector<HeightMap> scene::heightMaps = {
  HeightMap(HeightMapReader("../data/world.jpg"), 200, 200, 200, materials[0])
};

