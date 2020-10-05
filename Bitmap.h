//
// Created by erico on 12/07/2020.
//

#ifndef LEARNINGPIXMAN_BITMAP_H
#define LEARNINGPIXMAN_BITMAP_H

#include <memory>
#include "pixman.h"

class Bitmap {
public:
    Bitmap();
    Bitmap(int width, int height, int color_depth = 0);
    ~Bitmap();

    bool    Create(int width, int height, int color_depth = 0);
    bool    CreateTransparent(int width, int height, int color_depth = 0);

    // Create a copy of given bitmap
    bool	CreateCopy(Bitmap *src, int color_depth = 0);
    // Deallocate bitmap
    void	Destroy();

    bool    LoadFromFile(const char *filename);
    bool    SaveToFile(const char *filename, const void *palette);

    int  GetWidth() const;
    int  GetHeight() const;
    int  GetColorDepth() const;

    // BPP: bytes per pixel
    inline int  GetBPP() const
    {
        return (GetColorDepth() + 7) / 8;
    }

    // Checks if bitmap has zero size: either width or height (or both) is zero
    inline bool IsEmpty() const
    {
        return GetWidth() == 0 || GetHeight() == 0;
    }

     pixman_image_t* pm_image = nullptr;
    void SaveBMP24bpp(const char * filename) const;
};


#endif //LEARNINGPIXMAN_BITMAP_H
