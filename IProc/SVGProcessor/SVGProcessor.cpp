// Copyright 2017,2025 The OnePointer Authors.
//


#include "SVGProcessor.hpp"


namespace oneptr {
namespace IProc {


SVGProcessor::SVGProcessor()
    :   PictureProcessor()
{}

SVGProcessor::SVGProcessor(const SVGProcessor& orig)
    :   PictureProcessor( orig )
{}

SVGProcessor::~SVGProcessor() {}


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


void SVGProcessor::freeImageData(){
    imgDataStruct.imgPixArray = NULL;
}


} // namespace IProc
} // namespace oneptr
