#ifndef _AOR2P_SIMDIP_SUBI_H_
#define _AOR2P_SIMDIP_SUBI_H_

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_SUBI
subtract every pixel in image from constant
*/

#ifdef  __AVX512BW__

extern void avx512_subi_8bpc(uint8_t c);
#define simd_subi_8bpc(c) avx512_subi_8bpc(c)

#else

extern void avx2_subi_8bpc(uint8_t c);
#define simd_subi_8bpc(c) avx2_subi_8bpc(c)

#endif//__AVX512BW__

// simd, sub from constant, 8 bits per channel, no pipeline
void simd_subi_8bpc_npl(imgfile_t*, uint8_t);

// no simd, sub from constant, 8 bits per channel, no pipeline
void subi_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_SIMDIP_SUBI_H_
