#include "scene.h"


const Light scene::lights[] = {
  Light(Point3d(275, 549, 295))
};

const Material scene::materials[] = {
  Material(Color(0.2, 0.8, 0.2), 1, 0, 0)
};

const HeightMap scene::heightMaps[] = {
  HeightMap(HeightMapReader("../data/world.jpg"), 200, 200, 200, materials[0])
};

