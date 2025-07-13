// Copyright 2017,2025 The OnePointer Authors.
//


#include "TIFFProcessor/TIFFProcessor.hpp"


namespace oneptr {
namespace IProc {



TIFFProcessor::TIFFProcessor()
    :   PictureProcessor()
{}

TIFFProcessor::TIFFProcessor(const TIFFProcessor& orig)
    :   PictureProcessor( orig )
{}

TIFFProcessor::~TIFFProcessor() {}


bool TIFFProcessor::readImage(char * filename) {
  
    TIFF* tif = TIFFOpen(filename, "r");
    if (tif) {
	size_t npixels;
	uint32* raster;

	TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &imgWidth);
	TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &imgHeight);
        npixels = imgWidth * imgHeight;
	raster = (uint32*) _TIFFmalloc(npixels * sizeof (uint32));
	if (raster != NULL) {
	    if (TIFFReadRGBAImage(tif, imgWidth, imgHeight, raster, 0)) {
                fillRGBApixelArray(raster,npixels);
            }
	    _TIFFfree(raster);
	}
	TIFFClose(tif);
    }
    return true;
}

bool TIFFProcessor::writeImage (char * filename, ImageData& ImageData) {
  
    TIFF* tif = TIFFOpen(filename, "w");
    
    if(tif){
        uint32 imagelength, imagewidth;
        uint8 * buf;
        uint32 row, col;
        uint16 config, nsamples;
        imagewidth = ImageData.imgWidth ;
        imagelength = ImageData.imgHeight ;
        config = PLANARCONFIG_CONTIG ;
        nsamples = 3;

        TIFFSetField(tif, TIFFTAG_IMAGELENGTH, imagelength);
        TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, imagewidth);
        TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, nsamples);
        TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_LZW) ;
        TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8) ;
        TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(tif, imagewidth*nsamples));

        int pixPos = 0;
        buf = new uint8 [imagewidth*nsamples] ;
        for (row = 0; row < imagelength; row++){
            for(col=0; col < imagewidth; col++){
                buf[col*nsamples+0] = static_cast<uint8> (ImageData.imgPixArray[pixPos].r);
                buf[col*nsamples+1] = static_cast<uint8> (ImageData.imgPixArray[pixPos].g);
                buf[col*nsamples+2] = static_cast<uint8> (ImageData.imgPixArray[pixPos].b);
                buf[col*nsamples+3] = static_cast<uint8> (ImageData.imgPixArray[pixPos].a);
                pixPos++;
            }
            if (TIFFWriteScanline(tif, buf, row) != 1 ) break;
        }
        _TIFFfree(buf);
        TIFFClose(tif);
    }
    delete ImageData.imgPixArray;
    return true;
}

bool TIFFProcessor::fillRGBApixelArray(uint32* raster, int npixels){
    
    imgDataStruct.imgPixArray = new RGBApixel[npixels];
    imgDataStruct.imgHeight = imgHeight;
    imgDataStruct.imgWidth = imgWidth;
    int rasterPos = npixels-imgWidth;
    int row = imgHeight-1;
    int offset = 0;
    for(int pixPos = 0; pixPos < npixels; pixPos++){
        if ((pixPos+1)%imgWidth==0) offset = imgWidth;
        else offset = 0;
        imgDataStruct.imgPixArray[pixPos].r = raster[rasterPos+offset] & 0xFF;
        raster[rasterPos] >>= 8;
        imgDataStruct.imgPixArray[pixPos].g = raster[rasterPos+offset] & 0xFF;
        raster[rasterPos] >>= 8;
        imgDataStruct.imgPixArray[pixPos].b = raster[rasterPos+offset] & 0xFF;
        raster[rasterPos] >>= 8;
        imgDataStruct.imgPixArray[pixPos].a = raster[rasterPos+offset] & 0xFF;  
        rasterPos++;
        if ((rasterPos+1)%imgWidth == 0) {
            row--;
            rasterPos = imgWidth*row-1;
            if (rasterPos < 0) break;
        }
    }   
    return true;
}




} // namespace IProc
} // namespace oneptr
