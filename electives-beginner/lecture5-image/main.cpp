#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <cstring>
#include <iostream>

using namespace std;

void set_pixel(unsigned char* data, int h, int w, int row, int col, unsigned char color) {
    data[row * w + col] = color;
}

int main() {
    int h = 480;
    int w = 640;
    unsigned char* data = new unsigned char[h * w];

    memset(data, 255, h * w);

    for (int i = 0; i <= 255; ++i) {
        set_pixel(data, h, w, i, i, i);
    }

    int r = stbi_write_png("image.png", w, h, 1, data, w);

    cout << (r ? "OK" : "FAIL");

    return 0;
}
