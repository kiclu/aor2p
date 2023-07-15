#ifndef _AOR2P_OP_KERN_H_
#define _AOR2P_OP_KERN_H_

#include<stdlib.h>

#include<img/imgfile.h>

/*
OP_KERN
apply kernel to image
*/

typedef struct{
    float** kern;
    size_t n;
    size_t m;
} kern_t;

void simd_kswap_8bpc_npl_smt(imgfile_t*);

// simd, apply, kernel to pixel, 8 bits per channel, no pipeline, multithreaded
void simd_kern_8bpc_npl_smt(imgfile_t*, kern_t, size_t, size_t);

// simd, apply kernel to pixel, 8 bits per channel, no pipeline
void simd_kern_8bpc_npl(imgfile_t*, kern_t);

// no simd, apply kernel to pixel, 8 bits per channel, no pipeline
void kern_8bpc_npl(imgfile_t*, kern_t);

void kern_init(size_t, size_t);
void kern_free();

#endif//_AOR2_OP_KERN_H_
