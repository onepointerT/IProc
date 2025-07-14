// Copyright 2017,2025 The OnePointer Authors.
//

#pragma once

#include <cstring>
#include <string>

#include "JPEGProcessor/JPEGProcessor.hpp"
#include "BMPProcessor/BMPProcessor.hpp"
#include "PixelProcessor/PixelProcessor.hpp"
#include "PixelProcessor/pixel.h"
#include "PNGProcessor/PNGProcessor.hpp"
#include "TIFFProcessor/TIFFProcessor.hpp"


namespace oneptr {
namespace IProc {


/// @brief The main IProc class that manages the different formats of pictures to process with and edit.
class IProc {
public:
    IProc();
    IProc(const IProc& orig);
    virtual ~IProc();
    
    /// 
    /// @brief prints the version of the image library used [ libpng, libjpeg ]
    /// @return 
    int readImageFormatInfo(std::string);
    
    /// 
    /// 
    /// @param path of the image ( source or the target)
    /// @return an integer according to the image format
    /// 1 : PNG
    /// 2 : JPEG/JPG
    /// 3 : TIFF/TIF
    /// 4 : BMP
    int getImageFormat(std::string);
    
    /// 
    /// 
    /// @param imgPath path of the image source
    /// @return 1
    int readImage(std::string);
    /// 
    /// 
    /// @param imgPath path of the target image
    /// @return 1 
    int writeImage(std::string);
    /// 
    /// 
    /// @param imgPath path of the target image
    /// @return 1 
    int writeImage(std::string,int);
    
    int writeImage(std::string, std::string);
    
    /// 
    /// 
    /// @param x position of pixel
    /// @param y position of pixel
    /// @return RGBApixel data structure
    RGBApixel getPixel(int,int);
    /// 
    /// 
    /// @return ImageData
    ImageData getImageData();
    /// 
    /// 
    /// @param x position of pixel
    /// @param y position of pixel
    /// @param pixel new pixel to replace with the old pixel in that position
    /// @return 1
    int setPixel(int,int,RGBApixel);
    /// 
    /// 
    /// @param imgDataStruct image data structure
    /// @return 1
    int setImageData(ImageData imgDataStruct);
    
    /// 
    /// 
    /// @param targetWidth new width of the image
    /// @param targetHeight new height of the image
    /// @return 1
    int resize(int, int);
    /// 
    /// 
    /// @param row1
    /// @param col1
    /// @param row2
    /// @param col2
    /// @param originWidth
    /// @param OriginalArray
    /// @return 
    int crop(int, int, int, int);
    /// 
    /// 
    /// @param limit
    /// @return 
    int binary(int);
    /// 
    /// Convert the RGB pixel values to grayscale 
    /// @return 1 
    int grayscale();
    
    int testMethod();
    
private:
    
    PNGProcessor pngProc;
    JPEGProcessor jpegProc;
    TIFFProcessor tifProc;
    BMPProcessor bmpProc;
    PixelProcessor pixProc;
    ImageData imgDataStruct;
    
};




} // namespace IProc
} // namespace oneptr
