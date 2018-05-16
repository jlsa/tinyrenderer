#include <iostream>
#include "tgaimage.h"

struct Vector2
{
    int x;
    int y;
};

// ---- prototypes
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

// --- declarations
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char**argv)
{
    Vector2 imageSize;
    imageSize.x = 100;
    imageSize.y = 100;

    TGAImage image(imageSize.x, imageSize.y, TGAImage::RGB);

    line(13, 20, 80, 40, image, white); 
    line(20, 13, 40, 80, image, red); 
    line(80, 40, 13, 20, image, red);

    image.flip_vertically();    // origin at left bottom corner
    image.write_tga_file("output.tga");

    std::cout << "Creating output.tga complete." << std::endl;

    return 0;
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int dx = x1-x0; 
    int dy = y1-y0; 
    int derror2 = std::abs(dy) * 2; 
    int error2 = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= 1.; 
        } 
    } 
}

