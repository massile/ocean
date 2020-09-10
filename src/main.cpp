#include <iostream>
#include "simulation/HeightDisplacement.hpp"
#include "rendering/Image.hpp"

int main() {
  using namespace Ocean;
  Image image(RESOLUTION, RESOLUTION);

  GenerateSpectra();
  UpdateHeights(0);

  for (int i = 0; i < RESOLUTION*RESOLUTION; i++) {
    float grey = 0.05f * Ocean::heights[i] + 0.4f;
    image.pixels[i] = Color(grey, grey, grey);
  }

  image.Write("build/test.ppm");
}
