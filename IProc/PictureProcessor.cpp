// Copyright 2017,2025 The OnePointer Authors.
//


#include "PictureProcessor.hpp"


namespace oneptr {
namespace IProc {


PictureProcessor::PictureProcessor()
    :   imgHeight(0)
    ,   imgWidth(0)
    ,   imgDataStruct( *new ImageData{nullptr, 0, 0} )
{}

PictureProcessor::PictureProcessor(const PictureProcessor& orig)
    :   imgHeight(orig.imgHeight)
    ,   imgWidth(orig.imgWidth)
    ,   imgDataStruct( *new ImageData{orig.imgDataStruct.imgPixArray, orig.imgDataStruct.imgWidth, orig.imgDataStruct.imgHeight} )
{}

PictureProcessor::~PictureProcessor() {}


void PictureProcessor::setHeight(u_int height) {
    this->imgHeight = height;
}


void PictureProcessor::setWidth(u_int width) {
    this->imgWidth = width;
}


u_int PictureProcessor::getHeight() {
    return this->imgHeight;
}


u_int PictureProcessor::getWidth() {
    return this->imgWidth;
}


ImageData& PictureProcessor::getImageData(){
    return this->imgDataStruct;
}


void PictureProcessor::freeImageData(){
    imgDataStruct.imgPixArray = NULL;
}


} // namespace IProc
} // namespace oneptr
