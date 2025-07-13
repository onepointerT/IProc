// Copyright 2017,2025 The OnePointer Authors.
//

#pragma once

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>

#include "PixelProcessor/pixel.h"


namespace oneptr {
namespace IProc {

/// @brief The common `unsigned int` of the IProc library
typedef unsigned int u_int;
/// @brief The common `unsigned char` of the IProc library
typedef unsigned char u_char;

/// @brief The prototype, an abstract class for every image processor and image format to inherit from.
class PictureProcessor {
public:
    PictureProcessor();
    PictureProcessor(const PictureProcessor& orig);
    virtual ~PictureProcessor();
    
    /// @brief Read an image from file
    /// @param filename the path to the image
    /// @return true if read the image without any errors
    virtual bool readImage( char* path ) = 0;
    /// @brief Write an image to file
    /// @param filename target fie path
    /// @param ImageData pixel array of the image to be written
    /// @return true if write the image without any errors
    virtual bool writeImage( char* path, ImageData& imgData ) = 0;
    
    /// @brief Get the width of the image
    /// @return width of the image 
    virtual u_int getWidth();
    /// @brief Get the heigth of the image
    /// @return height of the image 
    virtual u_int getHeight();
    /// @brief Set the width of the image
    /// @param width of the image
    virtual void setWidth( u_int width );
    /// @brief Set the height of the image
    /// @param height of the image
    virtual void setHeight( u_int height );
    
    /// @brief Fill an RGBA pixel array from buffered data source
    /// @param buffer that contains decompressed image pixels 
    /// @param pixPos pixel position
    /// @param row_stride physical row width in image buffer
    /// @return true on success
    virtual bool fillRGBApixelArray( unsigned char*  buffer, u_int row, u_int byteSize );
    /// @brief Get the ImageData of this image
    /// @return ImageData that contains pixel array and image meta data 
    virtual ImageData& getImageData();
    
    
    /// @brief Free the pixel array in ImageData
    virtual void freeImageData();


protected:
    /// @brief The dimensions of the image
    u_int imgHeight,imgWidth;
    /// @brief All image data
    ImageData& imgDataStruct;

    friend class PictureProcessor;
};



} // namespace IProc
} // namespace oneptr
