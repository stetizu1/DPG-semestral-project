#include <GL/glut.h>
#include <src/heightmap-reader/HeightMapReader.h>
#include <vector>


#include "src/color/Color.h"


struct Bitmap {
  unsigned width, height;
  std::vector<Color> image;

  Bitmap(unsigned int width, unsigned int height)
    : width(width), height(height) {
    image.resize(width * height);
  }
};

HeightMapReader reader("../data/Sumava.png");
Bitmap bitmap(reader.getImageWidth(), reader.getImageHeight());

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
  Color c(counter, 0, 0);
  for (int y = 0; y < bitmap.height; y++) {
    for (int x = 0; x < bitmap.width; x++) {
      float k = reader.getIntensityAt(x, y);
      Color kk(k, k, k);
      bitmap.image[y * bitmap.width + x] = (kk + (c/4));
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

  glutInitWindowSize((int)bitmap.width, (int)bitmap.height);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutCreateWindow("Window Title");
  glutDisplayFunc(drawImage);
  glutKeyboardFunc(onKeys);

  glutIdleFunc(onFrame);

  glutMainLoop();

  return 0;
}
