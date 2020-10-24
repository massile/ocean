#pragma once

#include <fstream>
#include <cmath>

namespace Ocean {

  struct Color {
    float red;
    float green;
    float blue;

    Color() {}
    Color(float r, float g, float b) : red(r), green(g), blue(b) {}
  };

  struct Image {
    Color *pixels;
    int width, height;

    Image(int width, int height)
        : width(width), height(height), pixels(new Color[width * height]) {}

    void Write(const char *fileName) const {
      std::ofstream file(fileName, std::ofstream::binary);
      file << "P6" << '\n' << width << ' ' << height << "\n255\n";
      file.write(GetColorBuffer(), width*height*3);
      file.close();
    }

    char* GetColorBuffer() const {
      char* buffer = new char[width*height*3];
      for (int j = height -1, idx = 0; j >= 0; j--) 
      for (int i = 0; i < width; i++) {
        Color* pixel = &pixels[i + j*width];
        buffer[idx++] = std::min(255.f, std::max(0.f, 255.99f * pixel->red));
        buffer[idx++] = std::min(255.f, std::max(0.f, 255.99f * pixel->green));
        buffer[idx++] = std::min(255.f, std::max(0.f, 255.99f * pixel->blue));
      }

      return buffer;
    }
  };

} // namespace Ocean
