#ifndef _AOR2P_SIMDIP_ADD_H_
#define _AOR2P_SIMDIP_ADD_H_

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_ADD
add a constant to every pixel in the image
*/

#ifdef  __AVX512BW__

extern void avx512_add_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, uint8_t c);
#define simd_add_8bpc(ptr_r, ptr_g, ptr_b, c) avx512_add_8bpc(ptr_r, ptr_g, ptr_b, c)

#else

extern void avx2_add_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, uint8_t c);
#define simd_add_8bpc(ptr_r, ptr_g, ptr_b, c) avx2_add_8bpc(ptr_r, ptr_g, ptr_b, c)

#endif//__AVX512BW__

// simd, add constant, 8 bits per channel, no pipeline
void simd_add_8bpc_npl(imgfile_t*, uint8_t);

// no simd, add constant, 8 bits per channel, no pipeline
void add_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_SIMDIP_ADD_H_
