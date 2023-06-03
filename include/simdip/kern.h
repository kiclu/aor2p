#ifndef _SIMDIP_KERN_H
#define _SIMDIP_KERN_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_KERN
apply kernel to image
*/

typedef struct {
    int8_t** kern;
    size_t n;
    size_t m;
} kern_t;

// simd, apply kernel to pixel, .bmp, 8 bits per channel, pipeline
void simd_kern_bmp_8bpc(uint8_t*, uint8_t*, uint8_t*, kern_t);

// simd, apply kernel to pixel, .bmp, 8 bits per channel, no pipeline
void simd_kern_bmp_8bpc_npl(imgfile_t*, kern_t);

// no simd, apply kernel to pixel, .bmp, 8 bits per channel, no pipeline
void kern_bmp_8bpc_npl(imgfile_t*, kern_t);

#endif//_SIMDIP_KERN_H
