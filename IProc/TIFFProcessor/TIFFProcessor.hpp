// Copyright 2017,2025 The OnePointer Authors.
//

#pragma once

#include <stdio.h>
#include <iostream>
#include <tiffio.h>

#include "PixelProcessor/pixel.h"


namespace oneptr {
namespace IProc {


class TIFFProcessor {
public:
    TIFFProcessor();
    TIFFProcessor(const TIFFProcessor& orig);
    virtual ~TIFFProcessor();
    
    /// @brief Read an image from file
    /// @param filename the path to the image
    /// @return 1 if read the image without any errors
    int readImage(char* path);
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
    
    /// @brief Fill an RGBA pixel array from buffered data source
    /// @param raster that contains image pixels 
    /// @param npixels number of pixels
    /// @return 1
    int fillRGBApixelArray(uint32* raster,int npixels);
    /// @brief Get the ImageData of this image
    /// @return ImageData that contains pixel array and image meta data 
    ImageData getImageData();
    
    /// @brief Free the pixel array in ImageData
    /// @return 1
    int freeImageData();
    
private:
    /// @brief The dimensions of the image
    int imgHeight,imgWidth;
    /// @brief All image data
    ImageData imgDataStruct;

};


} // namespace IProc
} // namespace oneptr
