// Copyright 2017,2025 The OnePointer Authors.
//

#pragma once

#include <png.h>
#include <zlib.h>

#include "PictureProcessor.hpp"
#include "PixelProcessor/pixel.h"
#include "PNGProcessor/writepng.h"


namespace oneptr {
namespace IProc {


/// @brief The png processor for the PNG picture format
class PNGProcessor
    :   public PictureProcessor
{
public:
    PNGProcessor();
    PNGProcessor(const PNGProcessor& orig);
    virtual ~PNGProcessor();
    
    /// @brief Get the version info of libPNG
    void readPNGVersionInfo();
    /// @brief Read an image from file
    /// @param filename the path to the image
    /// @return true if read the image without any errors
    virtual bool readImage(char* path) override;
    /// @brief 
    /// @return 
    u_int processImage();
    /// @brief Write an image to file
    /// @param filename target fie path
    /// @param ImageData pixel array of the image to be written
    /// @return true if write the image without any errors
    virtual bool writeImage(char* path,ImageData&) override;
    
    /// @brief Get the width of the image
    /// @return width of the image 
    virtual u_int getWidth() override;
    /// @brief Get the heigth of the image
    /// @return height of the image 
    virtual u_int getHeight() override;
    /// @brief Set the width of the image
    /// @param width of the image
    virtual void setWidth(u_int width) override;
    /// @brief Set the height of the image
    /// @param height of the image
    virtual void setHeight(u_int height) override;
    
    /// @brief Get the pixel array as `png_bytep`
    /// @return A pointer of PNG bytes
    png_bytep* getPixelArray();
    
    /// @brief Fill an RGBA pixel array from buffered data source
    /// @param buffer that contains decompressed image pixels 
    /// @param pixPos pixel position
    /// @param row_stride physical row width in image buffer 
    /// @return true on success
    virtual bool fillRGBApixelArray();
    
protected:
    int colorType, bitDepth;
    png_uint_32 imgWidth, imgHeight;
    png_color_16p pBackground;
    unsigned char *red, *green, *blue;
    double gamma, displayExponent;

    friend class PNGProcessor;
};



} // namespace IProc
} // namespace oneptr
