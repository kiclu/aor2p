#ifndef _AOR2P_SIMDIP_DIV_H_
#define _AOR2P_SIMDIP_DIV_H_

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_DIV
divide every pixel in the image by constant
*/

#ifdef  __AVX512BW__

extern void avx512_div_8bpc(uint8_t c);
#define simd_div_8bpc(c) avx512_div_8bpc(c)

#else

extern void avx2_div_8bpc(uint8_t c);
#define simd_div_8bpc(c) avx2_div_8bpc(c)

#endif//__AVX512BW__

// simd, divide by constant, 8 bits per channel, no pipeline
void simd_div_8bpc_npl(imgfile_t*, uint8_t);

// no simd, divide by constant, 8 bits per channel, no pipeline
void div_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_SIMDIP_DIV_H_
