// Copyright 2017,2025 The OnePointer Authors.
//

#pragma once

#include "PictureProcessor.hpp"
#include "PixelProcessor/pixel.h"


namespace oneptr {
namespace IProc {

/// @brief The bitmap processor for the BMP format
class BMPProcessor
    :   public PictureProcessor
{
public:
    BMPProcessor();
    BMPProcessor(const BMPProcessor& orig);
    virtual ~BMPProcessor();
    
    /// @brief Read an image from file
    /// @param filename the path to the image
    /// @return true if read the image without any errors
    virtual bool readImage( char* path ) override;
    /// @brief Write an image to file
    /// @param filename target fie path
    /// @param ImageData pixel array of the image to be written
    /// @return true if write the image without any errors
    virtual bool writeImage( char* path, ImageData& imgData, u_int bBit );
    virtual bool writeImage( char* path, ImageData& imgData ) override;
    
    /// @brief Fill an RGBA pixel array from buffered data source
    /// @param buffer that contains decompressed image pixels 
    /// @param pixPos pixel position
    /// @param row_stride physical row width in image buffer 
    /// @return true on success
    virtual bool fillRGBApixelArray(unsigned char* data, u_int row, u_int byteSize) override;
};





} // namespace IProc
} // namespace oneptr
