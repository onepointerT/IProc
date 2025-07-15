// Copyright 2017,2025 The OnePointer Authors.
//


#include "SVGProcessor.hpp"


namespace oneptr {
namespace IProc {


SVGProcessor::SVGProcessor()
    :   PictureProcessor()
    ,   mImage( *new NSVGimage{0, 0, new NSVGshape{}} )
{}

SVGProcessor::SVGProcessor(const SVGProcessor& orig)
    :   PictureProcessor( orig )
    ,   mImage( *new NSVGimage{orig.mImage.width, orig.mImage.height, orig.mImage.shapes} )
{}

SVGProcessor::~SVGProcessor() {}


bool SVGProcessor::readImage( char* path ) {
    mImage = *nsvgParseFromFile( path, "px", 300 );
    return true;
}


bool SVGProcessor::writeImage( char* path, ImageData& imgData ) {
    return true;
}

void SVGProcessor::setHeight(u_int height) {
    this->imgHeight = height;
}


void SVGProcessor::setWidth(u_int width) {
    this->imgWidth = width;
}


u_int SVGProcessor::getHeight() {
    return this->imgHeight;
}


u_int SVGProcessor::getWidth() {
    return this->imgWidth;
}


bool SVGProcessor::fillRGBApixelArray( unsigned char*  buffer, u_int row, u_int byteSize ) {
    return true;
}


void SVGProcessor::freeImageData(){
    imgDataStruct.imgPixArray = NULL;
}


} // namespace IProc
} // namespace oneptr
