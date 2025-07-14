// Copyright 2017,2025 The OnePointer Authors.
//

#pragma once

#include "PictureProcessor.hpp"

namespace oneptr {
namespace IProc {


/// @brief The prototype, an abstract class for every image processor and image format to inherit from.
class SVGProcessor
    :   public PictureProcessor
{
public:
    SVGProcessor();
    SVGProcessor(const SVGProcessor& orig);
    virtual ~SVGProcessor();
    
    /// @brief Read an image from file
    /// @param filename the path to the image
    /// @return true if read the image without any errors
    virtual bool readImage( char* path ) override;
    /// @brief Write an image to file
    /// @param filename target fie path
    /// @param ImageData pixel array of the image to be written
    /// @return true if write the image without any errors
    virtual bool writeImage( char* path, ImageData& imgData ) override;
    
    /// @brief Get the width of the image
    /// @return width of the image 
    virtual u_int getWidth() override;
    /// @brief Get the heigth of the image
    /// @return height of the image 
    virtual u_int getHeight() override;
    /// @brief Set the width of the image
    /// @param width of the image
    virtual void setWidth( u_int width ) override;
    /// @brief Set the height of the image
    /// @param height of the image
    virtual void setHeight( u_int height ) override;
    
    /// @brief Fill an RGBA pixel array from buffered data source
    /// @param buffer that contains decompressed image pixels 
    /// @param pixPos pixel position
    /// @param row_stride physical row width in image buffer
    /// @return true on success
    virtual bool fillRGBApixelArray( unsigned char*  buffer, u_int row, u_int byteSize ) override;
    
    
    /// @brief Free the pixel array in ImageData
    virtual void freeImageData() override;


protected:


    friend class SVGProcessor;
};



} // namespace IProc
} // namespace oneptr
