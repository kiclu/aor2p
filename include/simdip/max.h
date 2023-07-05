#ifndef _AOR2P_SIMDIP_MAX_H_
#define _AOR2P_SIMDIP_MAX_H_

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_MAX
replace every pixel of image with maximum its value and constant
*/

#ifdef  __AVX512BW__

extern void avx512_max_8bpc(uint8_t c);
#define simd_max_8bpc(c) avx512_max_8bpc(c)

#else

extern void avx2_max_8bpc(uint8_t c);
#define simd_max_8bpc(c) avx2_max_8bpc(c)

#endif//__AVX512BW__

// simd, max, 8 bits per channel, no pipeline
void simd_max_8bpc_npl(imgfile_t*, uint8_t);

// no simd, max, 8 bits per channel, no pipeline
void max_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_SIMDIP_MAX_H_
