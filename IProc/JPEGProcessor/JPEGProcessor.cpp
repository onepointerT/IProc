// Copyright 2017,2025 The OnePointer Authors.
//


#include "JPEGProcessor/JPEGProcessor.hpp"


#include <cstdio>
#include <cstdlib>
#include <iostream>


namespace oneptr {
namespace IProc {



struct JPEGProcessor::error_mgr* JPEGProcessor::init_error_mgr() {
    return new JPEGProcessor::error_mgr{.pub = (jpeg_error_mgr&) *new jpeg_error_mgr{}, .setjmp_buffer = (jmp_buf&) *new jmp_buf(*new _JBTYPE(), *new _JBTYPE())};
}


JPEGProcessor::JPEGProcessor()
    :   PictureProcessor()
    ,   error_ptr( init_error_mgr() )
{}

JPEGProcessor::JPEGProcessor(const JPEGProcessor& orig)
    :   PictureProcessor( orig )
    ,   error_ptr( init_error_mgr() )
{}

JPEGProcessor::~JPEGProcessor() { }


bool JPEGProcessor::readImage( char* filename ) {
  
    struct jpeg_decompress_struct cinfo;

    struct error_mgr& jerr = *init_error_mgr();
    FILE* infile;		/* source file */
    JSAMPARRAY buffer;		/* Output row buffer */
    u_int row_stride;		/* physical row width in output buffer */

    if ((infile = std::fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "can't open %s\n", filename);
        return 0;
    }

    /* set up the normal JPEG error routines, then override error_exit. */
    cinfo.err = jpeg_std_error(&jerr.pub);
    
    /* Establish the setjmp return context for error_exit to use. */
    if (setjmp(jerr.setjmp_buffer)) {
        jpeg_destroy_decompress(&cinfo);
        std::fclose(infile);
        return 0;
    }
    
    /* initialize the JPEG decompression object. */
    jpeg_create_decompress(&cinfo);

    /* specify data source (eg, a file) */
    jpeg_stdio_src(&cinfo, infile);

    /* read file parameters with jpeg_read_header() */
    (void) jpeg_read_header(&cinfo, TRUE);
  
    /* set parameters for decompression */

    /* Start decompressor */
    (void) jpeg_start_decompress(&cinfo);
    
    this->setWidth(cinfo.output_width);
    this->setHeight(cinfo.output_height);

    /* JSAMPLEs per row in output buffer */
    row_stride = cinfo.output_width * cinfo.output_components;
    /* Make a one-row-high sample array that will go away when done with image */
    buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
    
    imgDataStruct.imgPixArray = new RGBApixel[imgHeight*imgWidth];
    imgDataStruct.imgHeight = imgHeight;
    imgDataStruct.imgWidth = imgWidth;
    
    u_int pixPos = 0;
    while (cinfo.output_scanline < cinfo.output_height) {
        (void) jpeg_read_scanlines(&cinfo, buffer, 1);
        this->fillRGBApixelArray(buffer, pixPos, row_stride);
        pixPos+=cinfo.output_width;
    }
    
    /* Finish decompression */
    (void) jpeg_finish_decompress(&cinfo);

    jpeg_destroy_decompress(&cinfo);

    std::fclose(infile);
    
    return true;
}

bool JPEGProcessor::writeImage ( char* filename, ImageData& ImageData ) {
  
    u_int quality = 100;  

    struct jpeg_compress_struct cinfo;

    struct jpeg_error_mgr jerr;
    FILE * outfile;		/* target file */
    JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
    JSAMPLE * buffer;           /* array with JSAMPLEs */
    u_int row_stride;		/* physical row width in image buffer */

    /* allocate and initialize JPEG compression object */
    cinfo.err = jpeg_std_error(&jerr);
    /* initialize the JPEG compression object. */
    jpeg_create_compress(&cinfo);

    /* specify data destination */
    if ((outfile = std::fopen(filename, "wb")) == NULL) {
        std::fprintf(stderr, "can't open %s\n", filename);
        std::exit(1);
    }
    jpeg_stdio_dest(&cinfo, outfile);
    
    /* set parameters for compression */
    cinfo.image_width = ImageData.imgWidth; 	/* image width and height, in pixels */
    cinfo.image_height = ImageData.imgHeight;
    cinfo.input_components = 3;		/* # of color components per pixel */
    cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
    
    jpeg_set_defaults(&cinfo);

    jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

    /* Start compressor */
    jpeg_start_compress(&cinfo, TRUE);

    row_stride = ImageData.imgWidth * 3;	/* JSAMPLEs per row in buffer */

    u_int RGBpixels = ImageData.imgHeight * ImageData.imgWidth;
    buffer = new JSAMPLE[RGBpixels * 3]; 
    u_int bufferPos = 0;
    for(u_int pixPos = 0; pixPos < RGBpixels; pixPos++){
        buffer[bufferPos] = ImageData.imgPixArray[pixPos].r;
        buffer[bufferPos+1] = ImageData.imgPixArray[pixPos].g;
        buffer[bufferPos+2] = ImageData.imgPixArray[pixPos].b;
        bufferPos += 3;
    }
  
    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = & buffer[cinfo.next_scanline * row_stride];
        (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    /* Finish compression */
    jpeg_finish_compress(&cinfo);
    /* close the output file. */
    std::fclose(outfile);
    /* release JPEG compression object */
    jpeg_destroy_compress(&cinfo);
    
    delete ImageData.imgPixArray;

    return 1;
}

void JPEGProcessor::error_exit (j_common_ptr cinfo) {
    (*cinfo->err->output_message) (cinfo);
    /* Return control to the setjmp point */
    longjmp(error_ptr->setjmp_buffer, 1);
}

bool JPEGProcessor::fillRGBApixelArray(JSAMPARRAY buffer, u_int pixPos, u_int row_stride){
    
    for(u_int i = 0; i < row_stride; i+=3){
        imgDataStruct.imgPixArray[pixPos].r = (u_int)buffer[0][i];
        imgDataStruct.imgPixArray[pixPos].g = (u_int)buffer[0][i+1];
        imgDataStruct.imgPixArray[pixPos].b = (u_int)buffer[0][i+2];
        imgDataStruct.imgPixArray[pixPos].a = 255;
        pixPos++;
    }
    return true;
}


bool JPEGProcessor::fillRGBApixelArray( unsigned char*  buffer, u_int row, u_int byteSize ) {
    return this->fillRGBApixelArray( buffer, row, byteSize );
}


} // namespace IProc
} // namespace oneptr
