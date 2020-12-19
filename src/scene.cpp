#include "scene.h"


int scene::sceneNumber = 0;

const std::vector<Point3d> scene::defaultCenter = {
  Point3d(275.f, 200.f, 0.f),
  Point3d(275.f, 200.f, 0.f),
  Point3d(275.f, 200.f, 0.f)
};

const std::vector<Vector3d> scene::defaultEye = {
  Vector3d(0.f, 575.f, -800.f),
  Vector3d(-600.f, 700.f, 0.f),
  Vector3d(275.f, 350.f, -1000.f)
};

const Vector3d scene::defaultUp = Vector3d(0.f, 1.f, 0.f);

const Color scene::defaultBgColor = Color(0.01f, 0.01f, 0.01f);

const std::vector<Light> scene::lights = {
  Light(Point3d(-275, 400, -250)),
  Light(Point3d(275, 680, 50)),
  Light(Point3d(-250, 350, -275))
};

const std::vector<Material> scene::materials = {
  Material(ColorChanging::FIELDS),
  Material(ColorChanging::LAVA),
  Material(ColorChanging::ICE)
};

std::vector<std::string> scene::heightMapPaths = {
  "../data/Simple.png",
  "../data/GrandCanyon.jpg",
  "../data/Sumava.png"
};

std::vector<Point3d> scene::heightMapPositions = {
  Point3d(0, 0, -150),
  Point3d(0, 0, -300),
  Point3d(-50, -100, -50)
};

std::vector<Vector3d> scene::heightMapDimensions = {
  Vector3d(500, 175, 500),
  Vector3d(550, 150, 550),
  Vector3d(680, 200, 680)
};

std::vector<HeightMap> scene::heightMaps = {};

