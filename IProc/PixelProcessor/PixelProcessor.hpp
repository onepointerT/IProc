// Copyright 2017,2025 The OnePointer Authors.
//

#pragma once

#include "PictureProcessor.hpp"
#include "PixelProcessor/pixel.h"


namespace oneptr {
namespace IProc {


/// @brief The pixel processor for generic pixel pictures
class PixelProcessor
    :   public PictureProcessor
{
public:
    PixelProcessor();
    PixelProcessor(const PixelProcessor& orig);
    virtual ~PixelProcessor();
    
    static RGBApixel& getPixel(int x, int y, ImageData&);
    
    /// @brief Resize the pixels to another dimension
    /// |-------------------------|
    /// |-------------------------|          |------|
    /// |-------------------------|  ==>     |------|
    /// |-------------------------|          |------|
    /// |-------------------------|
    /// 
    /// @param originWidth Original image width
    /// @param originHeight Original image height
    /// @param newWidth new image width
    /// @param newHeight new image height
    /// @param OriginalArray Original pixel Array
    /// @return resized pixel array
    u_int* resize(int, int, int, int, u_int*);
    
    /// @brief Resize the pixels to another dimension
    /// |-------------------------|
    /// |-------------------------|          |------|
    /// |-------------------------|  ==>     |------|
    /// |-------------------------|          |------|
    /// |-------------------------|
    /// 
    /// @param originWidth Original image width
    /// @param originHeight Original image height
    /// @param newWidth new image width
    /// @param newHeight new image height
    /// @param OriginalArray Original pixel Array
    /// @return resized pixel array
    ////
    unsigned char** resize(int, int, int, int, unsigned char**);
    
    /// @brief Crop the pixels to another dimension
    ///              col1           col2
    ///      |----------------------------------|
    /// row1 |---------+--------------+---------|
    ///      |----------------------------------|
    ///      |----------------------------------|
    /// row2 |---------+--------------+---------|
    ///      |----------------------------------|
    /// 
    /// @param row1 cropped image top row coordinate
    /// @param col1 cropped image left coordinate         
    /// @param row2 cropped image bottom coordinate
    /// @param col2 cropped image right coordinate 
    /// @param originWidth Original image width
    /// @param originHeight Original image height
    /// @param OriginalArray Original pixel array
    /// @return cropped image pixel array
    ////
    u_int* crop(int, int, int, int, int, u_int*);
    
    /// @brief Shear the pixels
    /// @param originWidth Original image width
    /// @param originHeight Original image height
    /// @param OriginalArray Original pixel array
    /// @return sheared pixel array
    u_int* shear();

    /// @brief Grayscale the pixels
    /// @param originWidth Original image width
    /// @param originHeight Original image height
    /// @param OriginalArray Original pixel array
    /// @return gray pixel array
    u_int* grayScale(int, int, u_int*);
    u_int* rotate();
    
    /// @brief Convert the pixel array to a binary pixel array
    /// @param originWidth Original image width
    /// @param originHeight Original image height
    /// @param limit pixel divider boundary
    /// @param OriginalArray Original pixel array
    /// @return binary pixel array
    ////
    u_int* binary(int, int, int, u_int*);
    
    virtual bool readImage( char* path ) override { return true; }
    virtual bool writeImage( char* path, ImageData& imgData ) override { return true; }

protected:
    int* pixelArray;

};



} // namespace IProc
} // namespace oneptr
