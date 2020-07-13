//
// Created by erico on 12/07/2020.
//

#include "bmp.h"
#include "pixman.h"
#include <fstream>

inline uint8_t write8(uint8_t c, std::ofstream &f){
    f.put(c);
    if(f.good()) return c;
    return EOF;
}

inline int write16(int w, std::ofstream &f){
    int b1, b2;
    b1 = (w & 0xFF00) >> 8;
    b2 = w & 0x00FF;

    if (write8(b2, f)==b2)
        if (write8(b1, f)==b1)
            return w;

    return EOF;
}

inline long write32(long l, std::ofstream &f){
    int b1, b2, b3, b4;

    b1 = (int)((l & 0xFF000000L) >> 24);
    b2 = (int)((l & 0x00FF0000L) >> 16);
    b3 = (int)((l & 0x0000FF00L) >> 8);
    b4 = (int)l & 0x00FF;

    if (write8(b4,f)==b4)
        if (write8(b3,f)==b3)
            if (write8(b2,f)==b2)
                if (write8(b1,f)==b1)
                    return l;
    return EOF;
}


void bmp::SaveBMP24bpp(const char *filename) {
    std::ofstream f;
    f.open(filename,  std::fstream::out | std::fstream::binary);

    int bfSize;
    int biSizeImage;
    int depth;
    int bpp;
    int i, j;
    int w, h;
    uint8_t * buffer = nullptr;
    int stride, s;

    pixman_image_t *copy; //used to create the bit data for the exported BMP

    w = pixman_image_get_width(surface);
    h = pixman_image_get_height(surface);

    copy = pixman_image_create_bits (PIXMAN_r8g8b8,
                                     w, h, NULL, 0);
    pixman_image_composite32 (PIXMAN_OP_SRC,
                              surface, NULL, copy,
                              0, 0, 0, 0,
                              0, 0, w, h);

    depth = pixman_image_get_depth(copy);
    stride = pixman_image_get_stride (copy);
    s = (stride >= 0)? stride : - stride;

    bpp = (depth == 8) ? 8 : 24;

    biSizeImage = s * h; /* (w*3 + filler) * h */
    bfSize = 54 + biSizeImage;       /* header + image data */

    /* file_header */
    write16(0x4D42, f);              /*  header field used to identify the BMP ("BM") */
    write32(bfSize, f);              /* size of the BMP file in bytes  */
    write16(0, f);                   /* Reserved */
    write16(0, f);                   /* Reserved */

    write32(54, f); /* offset, starting address of the image data bytes */

    /* info_header */
    write32(40, f);                  /* size of this header, in bytes (40) */
    write32(w, f);              /* bitmap width in pixels (signed integer)  */
    write32(h, f);              /* bitmap height in pixels (signed integer)  */
    write16(1, f);                   /* number of color planes (must be 1)  */
    write16(bpp, f);                 /* color depth, number of bits per pixel */
    write32(0, f);                   /* compression method being used. */
    write32(biSizeImage, f);         /* image size of raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps. */
    write32(0xB12, f);               /* horizontal resolution. (pixel per metre, signed integer) (0xB12 = 72 dpi) */
    write32(0xB12, f);               /* vertical resolution. (pixel per metre, signed integer)  */

    write32(0, f);                /* number of colors in the color palette */
    write32(0, f);                /* number of important colors used */

    buffer = (uint8_t *) pixman_image_get_data(copy);
    /* image data */
    for (i = h-1; i>=0; i--)
    {
        for (j = 0; j < s; j++)
        {
            write8(*((uint8_t *)buffer + i * stride + j), f);
        }
    }

    pixman_image_unref(copy);

    f.close();
}


