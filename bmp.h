//
// Created by erico on 12/07/2020.
//

#ifndef LEARNINGPIXMAN_BMP_H
#define LEARNINGPIXMAN_BMP_H

#include "pixman.h"

class bmp {
public:
    pixman_image_t* surface = nullptr;
    void SaveBMP24bpp(const char * filename);
};


#endif //LEARNINGPIXMAN_BMP_H
