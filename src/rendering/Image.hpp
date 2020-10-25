#pragma once

#include <fstream>
#include <cmath>
#include "../math/Vector.hpp"

namespace Ocean {
  using Color = Vector3;

  struct Image {
    Color *pixels;
    int width, height;

    Image(int width, int height)
        : width(width), height(height), pixels(new Color[width * height]) {}

    Color &operator()(int x, int y) const {
      return pixels[x + y * width];
    }

    void Write(const char *fileName) const {
      std::ofstream file(fileName, std::ofstream::binary);
      file << "P6" << '\n'
           << width << ' ' << height << "\n255\n";
      file.write(GetColorBuffer(), width * height * 3);
      file.close();
    }

    char *GetColorBuffer() const {
      char *buffer = new char[width * height * 3];
      for (int j = height - 1, idx = 0; j >= 0; j--)
        for (int i = 0; i < width; i++) {
          Color *pixel = &pixels[i + j * width];
          buffer[idx++] = std::min(255.f, std::max(0.f, 255.99f * pixel->x));
          buffer[idx++] = std::min(255.f, std::max(0.f, 255.99f * pixel->y));
          buffer[idx++] = std::min(255.f, std::max(0.f, 255.99f * pixel->z));
        }

      return buffer;
    }
  };

} // namespace Ocean
