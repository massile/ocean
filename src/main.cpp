#include <iostream>
#include <sstream>
#include "simulation/HeightDisplacement.hpp"
#include "rendering/Image.hpp"

int main() {
  using namespace Ocean;
  Image image(RESOLUTION, RESOLUTION);

  GenerateSpectra();

  for (int t = 0; t < 120; t++) {
    UpdateHeights(t*0.04f);

    for (int i = 0; i < RESOLUTION*RESOLUTION; i++) {
      float grey = 0.05f * Ocean::heights[i] + 0.4f;
      image.pixels[i] = Color(grey, grey, grey);
    }

    std::stringstream fileName;
    fileName << "build/" << t << ".ppm";
    image.Write(fileName.str().c_str());
  }
}
