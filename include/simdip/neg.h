#ifndef _SIMDIP_NEG_H
#define _SIMDIP_NEG_H

#include<simdip/subi.h>

/*
OP_NEG
apply negative effect to image
*/

// simd, negative, .bmp, 8 bits per channel, pipeline
inline void simd_neg_bmp_8bpc(__m256i* ptr_r, __m256i* ptr_g, __m256i* ptr_b){
    simd_subi_bmp_8bpc(ptr_r, ptr_g, ptr_b, 0xFF);
}

// simd, negative, .bmp, 8 bits per channel, no pipeline
inline void simd_neg_bmp_8bpc_npl(imgfile_t* imgfile){
    simd_subi_bmp_8bpc_npl(imgfile, 0xFF);
}

#endif//_SIMDIP_NEG_H
