// Copyright 2017,2025 The OnePointer Authors.
//

#pragma once

#include <iostream>
#include <cstdio>
#include <png.h>
#include <zlib.h>

#include "PixelProcessor/pixel.h"
#include "PNGProcessor/writepng.h"


namespace oneptr {
namespace IProc {



class PNGProcessor {
public:
    PNGProcessor();
    PNGProcessor(const PNGProcessor& orig);
    virtual ~PNGProcessor();
    
    /// @brief Get the version info of libPNG
    int readPNGVersionInfo();
    /// @brief Read an image from file
    /// @param filename the path to the image
    /// @return 1 if read the image without any errors
    int readImage(char* path);
    /// @brief 
    /// @return 
    int processImage();
    /// @brief Write an image to file
    /// @param filename target fie path
    /// @param ImageData pixel array of the image to be written
    /// @return 1 if write the image without any errors
    int writeImage(char* path,ImageData);
    
    /// @brief Get the width of the image
    /// @return width of the image 
    int getWidth();
    /// @brief Get the heigth of the image
    /// @return height of the image 
    int getHeight();
    /// @brief Set the width of the image
    /// @param width of the image
    /// @return 1
    int setWidth(int width);
    /// @brief Set the height of the image
    /// @param height of the image
    /// @return 1
    int setHeight(int height);
    
    /// @brief Get the pixel array as `png_bytep`
    /// @return A pointer of PNG bytes
    png_bytep* getPixelArray();
    
    /// @brief Fill an RGBA pixel array from buffered data source
    /// @param buffer that contains decompressed image pixels 
    /// @param pixPos pixel position
    /// @param row_stride physical row width in image buffer 
    /// @return 1
    int fillRGBApixelArray();
    /// @brief Get the ImageData of this image
    /// @return ImageData that contains pixel array and image meta data 
    ImageData getImageData();
    
    /// @brief Free the pixel array in ImageData
    /// @return 1
    int freeImageData();
    
private:
    int colorType, bitDepth;
    png_uint_32 imgWidth, imgHeight;  //unsigned int
    png_color_16p pBackground;
    unsigned char *red, *green, *blue;
    double gamma, displayExponent;
    ImageData imgDataStruct;

};



} // namespace IProc
} // namespace oneptr
