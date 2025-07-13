// Copyright 2017,2025 The OnePointer Authors.
//

#ifndef IPROC_PIXEL_H
#define IPROC_PIXEL_H

#ifdef __cplusplus


namespace oneptr {
namespace IProc {

extern "C" {
#endif

struct RGBApixel {
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 0;
};

struct ImageData {
    RGBApixel * imgPixArray;
    int imgWidth;
    int imgHeight;
};

#ifdef __cplusplus
}


} // namespace IProc
} // namespace oneptr

#endif

#endif /* IPROC_PIXEL_H_ */

