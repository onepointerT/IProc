// Copyright 2017,2025 The OnePointer Authors.
//

#pragma once

#include <stdio.h>
#include <cstring>
#include <iostream>
#include <fstream>

#include "PixelProcessor/pixel.h"


namespace oneptr {
namespace IProc {


class BMPProcessor {
public:
    BMPProcessor();
    BMPProcessor(const BMPProcessor& orig);
    virtual ~BMPProcessor();
    
    /// @brief Read an image from file
    /// @param filename the path to the image
    /// @return 1 if read the image without any errors
    int readImage( char* path );
    /// @brief Write an image to file
    /// @param filename target fie path
    /// @param ImageData pixel array of the image to be written
    /// @return 1 if write the image without any errors
    int writeImage( char* path, ImageData imgData, int bBit );
    
    /// @brief Get the width of the image
    /// @return width of the image 
    int getWidth();
    /// @brief Get the heigth of the image
    /// @return height of the image 
    int getHeight();
    /// @brief Set the width of the image
    /// @param width of the image
    /// @return 1
    int setWidth( int width );
    /// @brief Set the height of the image
    /// @param height of the image
    /// @return 1
    int setHeight( int height );
    
    /// @brief Fill an RGBA pixel array from buffered data source
    /// @param buffer that contains decompressed image pixels 
    /// @param pixPos pixel position
    /// @param row_stride physical row width in image buffer 
    /// @return 1
    int fillRGBApixelArray(unsigned char* data, int row, int byteSize);
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
