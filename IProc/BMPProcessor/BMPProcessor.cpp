// Copyright 2017,2025 The OnePointer Authors.
//


#include "BMPProcessor/BMPProcessor.hpp"


#include <cstdio>
#include <cstdlib>
#include <cstring>


namespace oneptr {
namespace IProc {


BMPProcessor::BMPProcessor()
    :   PictureProcessor()
{}

BMPProcessor::BMPProcessor(const BMPProcessor& orig)
    :   PictureProcessor( orig )
{}

BMPProcessor::~BMPProcessor() {}


bool BMPProcessor::readImage( char* filename ) {
    
    FILE* file = std::fopen( filename, "rb" );
    if ( file == NULL ) {
        return false;
    }

    unsigned char* info = new unsigned char[54];
    std::fread( info, sizeof(unsigned char), 54, file ); // read the 54-byte header

    // extract image height and width from header
    this->setWidth(*(u_int*)&info[18]);
    this->setHeight(*(u_int*)&info[22]);
    
    u_int bBit = *(u_int*)&info[28];
    u_int byteSize;
    if ( bBit == 24 ) byteSize = 3;
    else if ( bBit == 32 ) byteSize = 4;

    imgDataStruct.imgPixArray = new RGBApixel[imgWidth*imgHeight];
    imgDataStruct.imgHeight = imgHeight;
    imgDataStruct.imgWidth = imgWidth;
    
    u_int rowPadded = (imgWidth*byteSize + byteSize) & (~byteSize);
    unsigned char* data = new unsigned char[rowPadded];

    u_int row = imgHeight;
    for ( u_int i = 0; i < imgHeight; i++ ) {
        std::fread( data, sizeof(unsigned char), rowPadded, file ); row--;
        this->fillRGBApixelArray(data,row,byteSize);
    }
    
    delete[] info,data;
    std::fclose(file);
    return true;
}


bool BMPProcessor::writeImage( char* filename, ImageData& ImageData, u_int bBit ) {
    
    imgHeight = ImageData.imgHeight;
    imgWidth = ImageData.imgWidth;
    
    u_int byteSize;
    if ( bBit == 24 ) byteSize = 3;
    else if ( bBit == 32 ) byteSize = 4;
    
    FILE *file;
    unsigned char *img = NULL;
    u_int pixSize = byteSize*imgWidth*imgHeight;
    u_int filesize = 54 + pixSize;  
    img = (unsigned char*) std::malloc( byteSize*imgWidth*imgHeight );
    
    std::memset( img,0,pixSize );
    u_int x,y,r,g,b,a;
  
    if ( bBit == 24 ) {
        for ( u_int i = 0; i < imgWidth; i++ ) {
            for ( u_int j=0; j < imgHeight; j++ ) {
                x=i; y=(imgHeight-1)-j;
                r = ImageData.imgPixArray[x + y*imgWidth].r;
                g = ImageData.imgPixArray[x + y*imgWidth].g;
                b = ImageData.imgPixArray[x + y*imgWidth].b;
                img[(x+y*imgWidth)*3+2] = (unsigned char)(r);
                img[(x+y*imgWidth)*3+1] = (unsigned char)(g);
                img[(x+y*imgWidth)*3+0] = (unsigned char)(b);
            }
        }
    } else if ( bBit == 32 ) {
        for( u_int i = 0; i < imgWidth; i++ ) {
            for( u_int j = 0; j < imgHeight; j++ ) {
                x=i; y=(imgHeight-1)-j;
                r = ImageData.imgPixArray[x + y*imgWidth].r;
                g = ImageData.imgPixArray[x + y*imgWidth].g;
                b = ImageData.imgPixArray[x + y*imgWidth].b;
                a = ImageData.imgPixArray[x + y*imgWidth].a;
                img[(x+y*imgWidth)*4+3] = (unsigned char)(a);
                img[(x+y*imgWidth)*4+2] = (unsigned char)(r);
                img[(x+y*imgWidth)*4+1] = (unsigned char)(g);
                img[(x+y*imgWidth)*4+0] = (unsigned char)(b);
            }
        }
    }
    
    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[4] = {0,0,0,0};

    bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize>> 8);
    bmpfileheader[4] = (unsigned char)(filesize>>16);
    bmpfileheader[5] = (unsigned char)(filesize>>24);

    bmpinfoheader[4] = (unsigned char)(imgWidth);
    bmpinfoheader[5] = (unsigned char)(imgWidth>> 8);
    bmpinfoheader[6] = (unsigned char)(imgWidth>>16);
    bmpinfoheader[7] = (unsigned char)(imgWidth>>24);
    bmpinfoheader[8] = (unsigned char)(imgHeight);
    bmpinfoheader[9] = (unsigned char)(imgHeight>> 8);
    bmpinfoheader[10] = (unsigned char)(imgHeight>>16);
    bmpinfoheader[11] = (unsigned char)(imgHeight>>24);
    
    bmpinfoheader[14] = bBit;

    file = std::fopen( filename,"wb" );
    std::fwrite( bmpfileheader, 1, 14, file );
    std::fwrite( bmpinfoheader, 1, 40, file );
    for( u_int i = 0; i < imgHeight; i++ )
    {
        std::fwrite( img+(imgWidth*(imgHeight-i-1)*byteSize), byteSize, imgWidth, file );
        std::fwrite( bmppad, 1, (4-(imgWidth*byteSize)%4)%4, file );
    }

    delete ImageData.imgPixArray;
    std::free(img);
    std::fclose(file);
    
    return true;
}


bool BMPProcessor::writeImage( char* path, ImageData& imgData ) {
    return this->writeImage( path, imgData, 32 );
}


bool BMPProcessor::fillRGBApixelArray( unsigned char* data, u_int row, u_int byteSize ){

    u_int col = 0;
    size_t pixPos = row*imgWidth;
    if ( byteSize == 3) {
        for( u_int bytePos = 0; bytePos < imgWidth*3; bytePos += 3 ) {
            // pixel Order is Convert (B, G, R) in Bitmap
            imgDataStruct.imgPixArray[pixPos+col].r = (u_int)data[bytePos+2];
            imgDataStruct.imgPixArray[pixPos+col].g = (u_int)data[bytePos+1];
            imgDataStruct.imgPixArray[pixPos+col].b = (u_int)data[bytePos];
            imgDataStruct.imgPixArray[pixPos+col].a = 255;
            col++;
        }
    } else if ( byteSize == 4) {
        for(u_int bytePos = 0; bytePos < imgWidth*4; bytePos += 4) {
            imgDataStruct.imgPixArray[pixPos+col].a = (u_int)data[bytePos+3];
            imgDataStruct.imgPixArray[pixPos+col].r = (u_int)data[bytePos+2];
            imgDataStruct.imgPixArray[pixPos+col].g = (u_int)data[bytePos+1];
            imgDataStruct.imgPixArray[pixPos+col].b = (u_int)data[bytePos];
            col++;
        }
    }

    return true;
}


} // namespace IProc
} // namespace oneptr
