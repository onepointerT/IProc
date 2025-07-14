// Copyright 2017,2025 The OnePointer Authors.
//

#pragma once

#include <stdio.h>
#include <tiffio.h>

#include "PictureProcessor.hpp"
#include "PixelProcessor/pixel.h"


namespace oneptr {
namespace IProc {


/// @brief The tiff processor for the TIFF picture format
class TIFFProcessor
    :   public PictureProcessor
{
public:
    TIFFProcessor();
    TIFFProcessor(const TIFFProcessor& orig);
    virtual ~TIFFProcessor();
    
    /// @brief Read an image from file
    /// @param filename the path to the image
    /// @return true if read the image without any errors
    virtual bool readImage(char* path) override;
    /// @brief Write an image to file
    /// @param filename target fie path
    /// @param ImageData pixel array of the image to be written
    /// @return true if write the image without any errors
    bool writeImage(char* path,ImageData&) override;
    
    /// @brief Fill an RGBA pixel array from buffered data source
    /// @param raster that contains image pixels 
    /// @param npixels number of pixels
    /// @return true on success
    bool fillRGBApixelArray(uint32* raster,int npixels);
    

};


} // namespace IProc
} // namespace oneptr
