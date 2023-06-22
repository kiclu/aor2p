#ifndef _SIMDIP_SUBI_H
#define _SIMDIP_SUBI_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_SUBI
subtract every pixel in image from constant
*/

// simd, sub from constant, 8 bits per channel, pipeline
void simd_subi_8bpc(uint8_t*, uint8_t*, uint8_t*, uint8_t);

// simd, sub from constant, 8 bits per channel, no pipeline
void simd_subi_8bpc_npl(imgfile_t*, uint8_t);

// no simd, sub from constant, 8 bits per channel, no pipeline
void subi_8bpc_npl(imgfile_t*, uint8_t);

#endif//_SIMDIP_SUBI_H
