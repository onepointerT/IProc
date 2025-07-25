// Copyright 2017,2025 The OnePointer Authors.
//


//#include <iostream>
#include <algorithm>

#include "IProc/IProc.hpp"


namespace oneptr {
namespace IProc {



IProc::IProc() { }

IProc::IProc(const IProc& orig) { }

IProc::~IProc() { }


int IProc::getImageFormat(std::string path){
    // getting the image type from path (file extension)
    std::string extension;
    extension = path.substr(path.find_last_of(".") + 1);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    
    if (extension == "png") return 1;
    else if (extension == "jpeg") return 2;
    else if (extension == "jpg") return 2;
    else if (extension == "tiff") return 3;
    else if (extension == "tif") return 3;
    else if (extension == "bmp") return 4;
    else return 0;
    
}

int IProc::readImageFormatInfo(std::string path){
    if ( path == "png" ){
        pngProc.readPNGVersionInfo();
    } else { 
        fprintf(stderr, " Invalid Image Format or Image format is not supported by IProc\n");
    }
    return 0;
}


int IProc::readImage(std::string imgPath){
    
    char *path = new char[imgPath.length() + 1];
    strcpy(path, imgPath.c_str());
    
    switch(getImageFormat(imgPath)){
        case 1:
            pngProc.readImage(path);
            imgDataStruct = pngProc.getImageData();
            pngProc.freeImageData();
            break;
        case 2:
            jpegProc.readImage(path);
            imgDataStruct = jpegProc.getImageData();
            jpegProc.freeImageData();
            break;
        case 3:
            tifProc.readImage(path);
            imgDataStruct = tifProc.getImageData();
            tifProc.freeImageData();
            break;    
        case 4:
            bmpProc.readImage(path);
            imgDataStruct = bmpProc.getImageData();
            bmpProc.freeImageData();
            break;    
        default:
            fprintf(stderr, " Invalid Image Format or Image format is not supported by IProc\n");
    }
    delete [] path;
    return 1;
}

int IProc::writeImage(std::string imgPath){
    
    char *path = new char[imgPath.length() + 1];
    strcpy(path, imgPath.c_str());
    
    switch(getImageFormat(imgPath)){
        case 1:
            pngProc.writeImage(path,imgDataStruct);
            break;
        case 2:
            jpegProc.writeImage(path,imgDataStruct);
            break;    
        case 3:
            tifProc.writeImage(path,imgDataStruct);
            break;
        case 4:
            bmpProc.writeImage(path,imgDataStruct,32);
            break;    
        default:
            fprintf(stderr, " Invalid Image Format or Image format is not supported by IProc\n");
    }
    return 0;

}

int IProc::writeImage(std::string imgPath, int bBit){
    
    char *path = new char[imgPath.length() + 1];
    strcpy(path, imgPath.c_str());
    
    switch(getImageFormat(imgPath)){
        case 4:
            bmpProc.writeImage(path,imgDataStruct,bBit);
            break;    
        default:
            fprintf(stderr, " Invalid Image Format or Image format is not supported by IProc\n");
    }
    return 0;

}


RGBApixel IProc::getPixel(int x,int y){
    
    RGBApixel pixel;
    pixel = imgDataStruct.imgPixArray[x+(y*imgDataStruct.imgWidth)];
    return pixel;
}


ImageData IProc::getImageData(){
    
    return this->imgDataStruct;
}


int IProc::setPixel(int x,int y,RGBApixel pixel){ 
    
    imgDataStruct.imgPixArray[x+(y*imgDataStruct.imgWidth)] = pixel;
    return 1;
}


int IProc::setImageData(ImageData imgDataStruct){ 
    
    this->imgDataStruct = imgDataStruct;
    return 1;
}


int IProc::resize(int targetWidth, int targetHeight)  {    
    
    if (targetWidth == -1 && targetHeight == -1) {
        return 0;
    } else if (targetWidth == -1) {
        targetWidth = (int)(imgDataStruct.imgWidth)*targetHeight/imgDataStruct.imgHeight;
    } else if (targetHeight == -1) {
        targetHeight = (int)(imgDataStruct.imgHeight*targetWidth)/imgDataStruct.imgWidth;
    }
    targetWidth += targetWidth/5;
    targetHeight += targetHeight/5;       
    
    ImageData newImgDataStruct;
    newImgDataStruct.imgWidth = targetWidth;
    newImgDataStruct.imgHeight = targetHeight;
    newImgDataStruct.imgPixArray = new RGBApixel[targetWidth*targetHeight];

    int sourceWidth = imgDataStruct.imgWidth; 
    int sourceHeight = imgDataStruct.imgHeight; 
    
    RGBApixel a, b, c, d; 
    int x, y, index;
    int x_ratio = ((int)(sourceWidth - 1)) / targetWidth;
    int y_ratio = ((int)(sourceHeight - 1)) / targetHeight;
    int x_diff, y_diff, blue, red, green ;
    int offset = 0 ;

    for (int i = 0; i < targetHeight; i++) {
        for (int j = 0; j < targetWidth; j++) {
            x = (int)(x_ratio * j) ;
            y = (int)(y_ratio * i) ;
            x_diff = (x_ratio * j) - x ;
            y_diff = (y_ratio * i) - y ;
            index = (y * sourceWidth + x) ;                
            a = imgDataStruct.imgPixArray[index] ;
            b = imgDataStruct.imgPixArray[index + 1] ;
            c = imgDataStruct.imgPixArray[index + sourceWidth] ;
            d = imgDataStruct.imgPixArray[index + sourceWidth + 1] ;

            // blue element
            blue = (a.b)*(1-x_diff)*(1-y_diff) + (b.b)*(x_diff)*(1-y_diff) +
                   (c.b)*(y_diff)*(1-x_diff)   + (d.b)*(x_diff*y_diff);

            // green element
            green = (a.g)*(1-x_diff)*(1-y_diff) + (b.g)*(x_diff)*(1-y_diff) +
                    (c.g)*(y_diff)*(1-x_diff)   + (d.g)*(x_diff*y_diff);

            // red element
            red = (a.r)*(1-x_diff)*(1-y_diff) + (b.r)*(x_diff)*(1-y_diff) +
                  (c.r)*(y_diff)*(1-x_diff)   + (d.r)*(x_diff*y_diff);

            newImgDataStruct.imgPixArray[offset].r = (int)red;
            newImgDataStruct.imgPixArray[offset].g = (int)green;
            newImgDataStruct.imgPixArray[offset].b = (int)blue;
            newImgDataStruct.imgPixArray[offset].a = 255;  
            offset++;
        }
    }
    this->imgDataStruct = newImgDataStruct;
    return 1;
}


int IProc::crop(int row1, int col1, int row2, int col2){
    
    int newHeight = row2 - row1;
    int newWidth = col2 - col1;
    int newPixelSize = newWidth * newHeight;
    int row, pos;
    ImageData newImageData;
    newImageData.imgHeight = newHeight;
    newImageData.imgWidth = newWidth;
    newImageData.imgPixArray = new RGBApixel[newPixelSize];
    for ( int i = 0; i < newPixelSize; i++ ) {
        row = row1 + (int)(i/newWidth);
        pos = (imgDataStruct.imgWidth * row) + col1 + (i % newWidth);
        newImageData.imgPixArray[i] = imgDataStruct.imgPixArray[pos];
    }
    imgDataStruct = newImageData;
    return 1;
}


int IProc::grayscale(){
    
    int pixSize = imgDataStruct.imgWidth*imgDataStruct.imgHeight;
    RGBApixel pix;
    int grayPixVal;
    for(int i = 0; i < pixSize; i++){
        pix = imgDataStruct.imgPixArray[i];
//        grayPixVal = (pix.r>>2) + (pix.g>>1) + (pix.b>>2);
        grayPixVal = (int)((pix.r + pix.g + pix.b)/3);
        pix.r = grayPixVal;
        pix.g = grayPixVal;
        pix.b = grayPixVal;
        imgDataStruct.imgPixArray[i] = pix;
    }
    return 1;
}

int IProc::binary(int limit){
    
    int pixSize = imgDataStruct.imgWidth * imgDataStruct.imgHeight;
    int grayVal,binVal;
    RGBApixel pix;
    for (int i = 0; i < pixSize; i++) {
        pix = imgDataStruct.imgPixArray[i];
        grayVal  = (int)((pix.r + pix.g + pix.b)/3);
        if (grayVal > limit) binVal = 255; 
        else binVal = 0;
        pix.r = binVal;
        pix.g = binVal;
        pix.b = binVal;
        imgDataStruct.imgPixArray[i] = pix;
    }
    return 1;
}


} // namespace IProc
} // namespace oneptr
