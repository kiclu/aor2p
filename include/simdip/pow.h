#ifndef _AOR2P_SIMDIP_POW_H_
#define _AOR2P_SIMDIP_POW_H_

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_POW
raise every pixel of image to power of constant
*/

#ifdef  __AVX512BW__

extern void avx512_pow_8bpc(uint8_t c);
#define simd_pow_8bpc(c) avx512_pow_8bpc(c)

#else

extern void avx2_pow_8bpc(uint8_t c);
#define simd_pow_8bpc(c) avx2_pow_8bpc(c)

#endif//__AVX512BW__

// simd, pow, 8 bits per channel, no pipeline
void simd_pow_8bpc_npl(imgfile_t*, uint8_t);

// no simd, pow, 8 bits per channel, no pipeline
void pow_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_SIMDIP_POW_H_
