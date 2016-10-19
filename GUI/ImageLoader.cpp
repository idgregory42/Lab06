#include "ImageLoader.h"
#include <windows.h>

#include <iostream>
using namespace std;

Glib::RefPtr<Gdk::Pixbuf> ImageLoader::loadImageRGBA(const char* id)
{
    HINSTANCE hInst = GetModuleHandle(0);
    HANDLE hBitMap = LoadImage(hInst, id, IMAGE_BITMAP, 0, 0, LR_COLOR);
    BITMAP bitmap;
    GetObject(hBitMap, sizeof(BITMAP), &bitmap);

    int width = bitmap.bmWidth;
    int height = bitmap.bmHeight;
    int depth = bitmap.bmBitsPixel;
    int size = height*width*depth/8;

    byte* lpBits = new byte[size];
    GetBitmapBits((HBITMAP) hBitMap, size, lpBits);

    byte* rgb = new byte[(size*4)/4];

    int count = 0;
    for (int i = 0; i < size; i += 4)
    {
       rgb[count + 3] = lpBits[i + 3];  //a
       rgb[count + 2] = lpBits[i];  //b
       rgb[count + 1] = lpBits[i + 1];  //g
       rgb[count] = lpBits[i + 2];  //r
       count += 4;
    }

    delete[] lpBits;

    //the bool parameter is hasalpha
    Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_data(rgb, Gdk::COLORSPACE_RGB, true, 8, width, height, 4*width);
    return image;
}

Glib::RefPtr<Gdk::Pixbuf> ImageLoader::loadImageRGB(const char* id)
{
    HINSTANCE hInst = GetModuleHandle(0);
    HANDLE hBitMap = LoadImage(hInst, id, IMAGE_BITMAP, 0, 0, LR_COLOR);
    BITMAP bitmap;
    GetObject(hBitMap, sizeof(BITMAP), &bitmap);

    int width = bitmap.bmWidth;
    int height = bitmap.bmHeight;
    int depth = bitmap.bmBitsPixel;
    int size = height*width*depth/8;

    byte* lpBits = new byte[size];
    GetBitmapBits((HBITMAP) hBitMap, size, lpBits);

    byte* rgb = new byte[size*3/4];

    int count = 0;
    for (int i = 0; i < size; i += 4)
    {
       rgb[count + 2] = lpBits[i];  //b
       rgb[count + 1] = lpBits[i + 1];  //g
       rgb[count] = lpBits[i + 2];  //r
       //skip alpha
       count += 3;
    }

    delete[] lpBits;

    //the bool parameter is hasalpha
    Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_data(rgb, Gdk::COLORSPACE_RGB, false, 8, width, height, 3*width);
    return image;
}
