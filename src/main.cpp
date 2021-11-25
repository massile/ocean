#include <iostream>
#include <sstream>
#include "simulation/HeightDisplacement.hpp"
#include "rendering/Render.hpp"

int main() {
  using namespace Ocean;
  Image image(512, 512*9/16);

  GenerateSpectra();
  for (int i = 0; i < 1024; i++) {
    printf("Saving frame %d...", i);
    UpdateHeights(i*0.016f);
    Draw(image);

    std::stringstream str;
    str << "build/" << i << ".ppm";
    image.Write(str.str().c_str());
  }

  system("ffmpeg -y -i build/%d.ppm build/test.mp4");
}
