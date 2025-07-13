// Copyright 2017,2025 The OnePointer Authors.
//

#ifndef IPROC_WRITEPNG_H_
#define IPROC_WRITEPNG_H_


#ifdef __cplusplus


namespace oneptr {
namespace IProc {

extern "C" {
#endif

#include <setjmp.h>
#include <stdio.h>
#include <time.h>

typedef struct _mainprog_info {
    double gamma;
    long width;
    long height;
    time_t modtime;
    FILE *infile;
    FILE *outfile;
    void *png_ptr;
    void *info_ptr;
    unsigned char *image_data;
    unsigned char **row_pointers;
    char *title = 0;
    char *author = 0;
    char *desc = 0;
    char *copyright = 0;
    char *email = 0;
    char *url = 0;
    int filter;
    int pnmtype;
    int sample_depth;
    int interlaced;
    int have_bg;
    int have_time;
    int have_text;
    jmp_buf jmpbuf;
    unsigned char bg_red;
    unsigned char bg_green;
    unsigned char bg_blue;
} mainprog_info;


#ifdef __cplusplus
}



} // namespace IProc
} // namespace oneptr

#endif


#endif /* IPROC_WRITEPNG_H_ */

