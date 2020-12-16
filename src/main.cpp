#include <GL/glut.h>
#include <vector>
#include <chrono>

#include "scene.h"
#include "src/context/Context.h"


struct Bitmap {
  unsigned width, height;
  std::vector<Color> image;

  Bitmap(unsigned int width, unsigned int height)
    : width(width), height(height) {
    image.resize(width * height);
  }
};

Bitmap bitmap(scene::defaultWidth, scene::defaultHeight);
Context *pContext;

void drawImage() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawPixels(bitmap.width, bitmap.height, GL_RGB, GL_FLOAT, bitmap.image.data());

  glutSwapBuffers();
}

void onFrame() {
  if (pContext == nullptr) return;
  for (int y = 0; y < bitmap.width; y++) {
    for (int x = 0; x < bitmap.height; x++) {
      auto color = pContext->getColorBuffer()[x][y];
      bitmap.image[x + bitmap.height * y] = color;
    }
  }
  glutPostRedisplay();
}

void onKeys(unsigned char key, int x, int y) {
  switch (key) {
    case 27:// ESC
      exit(0);
  }
}

int main(int argc, char **argv) {
  if (argc > 1) {
    auto s = argv[1];
    if (s[0] == '0') {
      scene::sceneNumber = 0;
    } else if (s[0] == '1') {
      scene::sceneNumber = 1;
    } else {
      scene::sceneNumber = 2;
    }
  }
  auto context = Context();
  pContext = &context;

  glutInit(&argc, argv);

  glutInitWindowSize((int) bitmap.width, (int) bitmap.height);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutCreateWindow("Window Title");
  glutDisplayFunc(drawImage);
  glutKeyboardFunc(onKeys);

  glutIdleFunc(onFrame);

  glutMainLoop();

  return 0;
}
