#ifndef _AOR2P_SIMDIP_MIN_H_
#define _AOR2P_SIMDIP_MIN_H_

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_MIN
replace every pixel of image with minimum its value and constant
*/

#ifdef  __AVX512BW__

extern void avx512_min_8bpc(uint8_t c);
#define simd_min_8bpc(c) avx512_min_8bpc(c)

#else

extern void avx2_min_8bpc(uint8_t c);
#define simd_min_8bpc(c) avx2_min_8bpc(c)

#endif//__AVX512BW__

// simd, min, 8 bits per channel, no pipeline
void simd_min_8bpc_npl(imgfile_t*, uint8_t);

// no simd, min, 8 bits per channel, no pipeline
void min_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_SIMDIP_MIN_H_
