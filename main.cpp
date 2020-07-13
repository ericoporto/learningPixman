#include <iostream>
#include "pixman.h"
#include "bmp.h"

int main() {
    const pixman_color_t black = { 0, 0, 0, 0xffff };
    const pixman_color_t white = {0xffff, 0xffff, 0xffff, 0xffff };
    const pixman_color_t red = { 0xffff, 0, 0, 0xffff };
    const pixman_color_t green = { 0, 0xffff, 0, 0xffff };
    const pixman_color_t blue = { 0, 0, 0xffff, 0xffff };
    const int width = 555;
    const int height = 333;
    pixman_image_t* surface = nullptr;
    pixman_image_t *fill = nullptr;

    bmp* myBmp = new bmp();

    myBmp->pm_image = pixman_image_create_bits(PIXMAN_r8g8b8a8, width, height, NULL, 0);

    fill = pixman_image_create_solid_fill(&white);
    pixman_image_composite(PIXMAN_OP_SRC, fill, NULL, myBmp->pm_image , 0, 0, 0, 0, 0, 0, width, height);

    fill = pixman_image_create_solid_fill(&red);
    pixman_image_composite(PIXMAN_OP_SRC, fill, NULL, myBmp->pm_image , 0, 0, 0, 0, 2, 2, 8, 8);

    myBmp->SaveBMP24bpp("test.bmp");

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
