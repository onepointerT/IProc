// Copyright 2017,2025 The OnePointer Authors.
//


#include "BMPProcessor/BMPProcessor.hpp"


namespace oneptr {
namespace IProc {


BMPProcessor::BMPProcessor() { }

BMPProcessor::BMPProcessor(const BMPProcessor& orig) { }

BMPProcessor::~BMPProcessor() { }

int BMPProcessor::setHeight(int height) {
    this->imgHeight = height;
    return 1;
}


int BMPProcessor::setWidth(int width) {
    this->imgWidth = width;
    return 1;
}


int BMPProcessor::getHeight() {
    return this->imgHeight;
}


int BMPProcessor::getWidth() {
    return this->imgWidth;
}

int BMPProcessor::readImage(char * filename) {
    
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        std::cout<<"error in the file '"<<filename<<"'";
        return 0;
    }    
    unsigned char * info = new unsigned char[54];
    fread(info, sizeof(unsigned char), 54, file); // read the 54-byte header

    // extract image height and width from header
    setWidth(*(int*)&info[18]);
    setHeight(*(int*)&info[22]);
    
    int bBit = *(int*)&info[28];
    int byteSize;
    if (bBit == 24) byteSize = 3;
    else if (bBit == 32) byteSize = 4;

    imgDataStruct.imgPixArray = new RGBApixel[imgWidth*imgHeight];
    imgDataStruct.imgHeight = imgHeight;
    imgDataStruct.imgWidth = imgWidth;
    
    int rowPadded = (imgWidth*byteSize + byteSize) & (~byteSize);
    unsigned char* data = new unsigned char[rowPadded];

    int row = imgHeight;
    for(int i = 0; i < imgHeight; i++) {
        fread(data, sizeof(unsigned char), rowPadded, file); row--;
        fillRGBApixelArray(data,row,byteSize);
    }
    
    delete info,data;
    fclose(file);
    return 1;
}

int BMPProcessor::writeImage (char * filename, ImageData ImageData, int bBit = 32) {
    
    imgHeight = ImageData.imgHeight;
    imgWidth = ImageData.imgWidth;
    
    int byteSize;
    if (bBit == 24) byteSize = 3;
    else if (bBit == 32) byteSize = 4;
    
    FILE *file;
    unsigned char *img = NULL;
    int pixSize = byteSize*imgWidth*imgHeight;
    int filesize = 54 + pixSize;  
    img = (unsigned char *)malloc(byteSize*imgWidth*imgHeight);
    
    memset(img,0,pixSize);
    int x,y,r,g,b,a;
  
    if (bBit == 24) {
        for(int i=0; i<imgWidth; i++) {
            for(int j=0; j<imgHeight; j++) {
                x=i; y=(imgHeight-1)-j;
                r = ImageData.imgPixArray[x + y*imgWidth].r;
                g = ImageData.imgPixArray[x + y*imgWidth].g;
                b = ImageData.imgPixArray[x + y*imgWidth].b;
                img[(x+y*imgWidth)*3+2] = (unsigned char)(r);
                img[(x+y*imgWidth)*3+1] = (unsigned char)(g);
                img[(x+y*imgWidth)*3+0] = (unsigned char)(b);
            }
        }
    } else if (bBit == 32) {
        for(int i=0; i<imgWidth; i++) {
            for(int j=0; j<imgHeight; j++) {
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

    file = fopen(filename,"wb");
    fwrite(bmpfileheader,1,14,file);
    fwrite(bmpinfoheader,1,40,file);
    for(int i=0; i<imgHeight; i++)
    {
        fwrite(img+(imgWidth*(imgHeight-i-1)*byteSize),byteSize,imgWidth,file);
        fwrite(bmppad,1,(4-(imgWidth*byteSize)%4)%4,file);
    }

    delete ImageData.imgPixArray;
    free(img);
    fclose(file);
    
    return 1;
}

ImageData BMPProcessor::getImageData(){
    return this->imgDataStruct;
}

int BMPProcessor::fillRGBApixelArray(unsigned char* data, int row, int byteSize){

    int col = 0;
    int pixPos = row*imgWidth;
    if ( byteSize == 3) {
        for(int bytePos = 0; bytePos < imgWidth*3; bytePos += 3) {
            // pixel Order is Convert (B, G, R) in Bitmap
            imgDataStruct.imgPixArray[pixPos+col].r = (int)data[bytePos+2];
            imgDataStruct.imgPixArray[pixPos+col].g = (int)data[bytePos+1];
            imgDataStruct.imgPixArray[pixPos+col].b = (int)data[bytePos];
            imgDataStruct.imgPixArray[pixPos+col].a = 255;
            col++;
        }
    } else if ( byteSize == 4) {
        for(int bytePos = 0; bytePos < imgWidth*4; bytePos += 4) {
            imgDataStruct.imgPixArray[pixPos+col].a = (int)data[bytePos+3];
            imgDataStruct.imgPixArray[pixPos+col].r = (int)data[bytePos+2];
            imgDataStruct.imgPixArray[pixPos+col].g = (int)data[bytePos+1];
            imgDataStruct.imgPixArray[pixPos+col].b = (int)data[bytePos];
            col++;
        }
    }   
    return 1;
}

int BMPProcessor::freeImageData(){
    imgDataStruct.imgPixArray = NULL;
    return 1;
}


} // namespace IProc
} // namespace oneptr
