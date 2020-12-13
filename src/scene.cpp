#include "scene.h"


const Point3d scene::defaultCenter = Point3d(275.f, 275.f, 0.f);

const Vector3d scene::defaultEye = Vector3d(275.f, 575.f, -800.f);

const Vector3d scene::defaultUp = Vector3d(0.f, 1.f, 0.f);

const Color scene::defaultBgColor = Color(0.05f, 0.05f, 0.05f);

const std::vector<Light> scene::lights = {
  Light(Point3d(275, 680, 50))
};

const std::vector<Material> scene::materials = {
  Material(Color(1, 0.8, 0.7), 1, 0, 0)
};

const std::vector<HeightMap> scene::heightMaps = {
  HeightMap(HeightMapReader("../data/test2.png"), Point3d(0, 0, 50), 550, 160, 550, materials[0])
};

