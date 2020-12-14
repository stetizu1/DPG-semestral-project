#include "scene.h"


int scene::sceneNumber = 0;

const std::vector<Point3d> scene::defaultCenter = {
  Point3d(275.f, 200.f, 0.f),
  Point3d(275.f, 200.f, 0.f),
  Point3d(275.f, 200.f, 0.f)
};

const std::vector<Vector3d> scene::defaultEye = {
  Vector3d(275.f, 500.f, -800.f),
  Vector3d(-800.f, 575.f, 0.f),
  Vector3d(275.f, 575.f, -800.f)
};

const Vector3d scene::defaultUp = Vector3d(0.f, 1.f, 0.f);

const Color scene::defaultBgColor = Color(0.05f, 0.05f, 0.05f);

const std::vector<Light> scene::lights = {
  Light(Point3d(-250, 350, -275)),
  Light(Point3d(275, 680, 50)),
  Light(Point3d(450, 200, 250))
};

const std::vector<Material> scene::materials = {
  Material(ColorChanging::ICE),
  Material(ColorChanging::LAVA),
  Material(ColorChanging::FIELDS)
};

const std::vector<HeightMap> scene::heightMaps = {
  HeightMap(HeightMapReader("../data/Sumava.png"), Point3d(-50, 0, -50), 680, 200, 680, materials[0]),
  HeightMap(HeightMapReader("../data/grand_canyon.jpg"), Point3d(0, 0, -300), 550, 150, 550, materials[1]),
  HeightMap(HeightMapReader("../data/vzorek.png"), Point3d(0, 0, -150), 500, 175, 500, materials[2])
};

