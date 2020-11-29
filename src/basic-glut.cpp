#include <GL/glut.h>
#include <iostream>
#include <vector>

#include "src/color/Color.h"


struct Bitmap {
  int width;
  int height;
  std::vector<Color> image;

  Bitmap(int width, int height)
      : width(width), height(height) {
    image.resize(width * height);
  }
};

Bitmap bitmap(512, 512);

void drawImage() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawPixels(bitmap.width, bitmap.height, GL_RGB, GL_FLOAT, bitmap.image.data());

  glutSwapBuffers();
}

void onFrame() {
  static float counter = 0;
  counter += 0.01f;
  if (counter > 1) {
    counter = 0;
  }
  Color c(counter, counter, counter);
  std::cout << c << "\n";
  for (int y = 0; y < bitmap.height; y++) {
    for (int x = 0; x < bitmap.width; x++) {
      bitmap.image[y * bitmap.width + x] = {counter, 0, 0};
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
  glutInit(&argc, argv);

  glutInitWindowSize(bitmap.width, bitmap.height);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutCreateWindow("Window Title");
  glutDisplayFunc(drawImage);
  glutKeyboardFunc(onKeys);

  glutIdleFunc(onFrame);

  glutMainLoop();

  return 0;
}
