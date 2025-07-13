// Copyright 2017,2025 The OnePointer Authors.
//

#pragma once


#include <csetjmp>
#include <jpeglib.h>

#include "PictureProcessor.hpp"
#include "PixelProcessor/pixel.h"


namespace oneptr {
namespace IProc {


/// @brief The jpeg processor for the JPEG picture format
class JPEGProcessor
    :   public PictureProcessor
{
public:
    JPEGProcessor();
    JPEGProcessor(const JPEGProcessor& orig);
    virtual ~JPEGProcessor();
    
    /// @brief Read an image from file
    /// @param filename the path to the image
    /// @return true if read the image without any errors
    virtual bool readImage( char* path ) override;
    /// @brief Write an image to file
    /// @param filename target fie path
    /// @param ImageData pixel array of the image to be written
    /// @return true if write the image without any errors
    virtual bool writeImage( char* path, ImageData& imgData ) override;
    
    /// @brief Fill an RGBA pixel array from buffered data source
    /// @param buffer that contains decompressed image pixels 
    /// @param pixPos pixel position
    /// @param row_stride physical row width in image buffer 
    /// @return true on success
    bool fillRGBApixelArray( JSAMPARRAY buffer, u_int pixPos, u_int row_stride );
    virtual bool fillRGBApixelArray( unsigned char*  buffer, u_int row, u_int byteSize ) override;
    
    void error_exit(j_common_ptr);
    
    struct error_mgr {
        struct jpeg_error_mgr& pub;
        jmp_buf& setjmp_buffer;
    };

    static struct error_mgr* init_error_mgr();
    
protected:
    error_mgr* error_ptr;

};




} // namespace IProc
} // namespace oneptr
