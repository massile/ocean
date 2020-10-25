#include <iostream>
#include <sstream>
#include "simulation/HeightDisplacement.hpp"
#include "rendering/Render.hpp"

int main() {
  using namespace Ocean;
  Image image(800, 600);
  Draw(image);

  image.Write("build/test.ppm");
  system("ffmpeg -y -i build/test.ppm build/test.png");
}
