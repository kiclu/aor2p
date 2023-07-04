#ifndef _AOR2P_SIMDIP_SUB_H_
#define _AOR2P_SIMDIP_SUB_H_

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_SUB
subtract a constant from every pixel in the image
*/

#ifdef  __AVX512BW__

extern void avx512_sub_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, uint8_t c);
#define simd_sub_8bpc(ptr_r, ptr_g, ptr_b, c) avx512_sub_8bpc(ptr_r, ptr_g, ptr_b, c)

#else

extern void avx2_sub_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, uint8_t c);
#define simd_sub_8bpc(ptr_r, ptr_g, ptr_b, c) avx2_sub_8bpc(ptr_r, ptr_g, ptr_b, c)

#endif//__AVX512BW__

// simd, sub constant, 8 bits per channel, no pipeline
void simd_sub_8bpc_npl(imgfile_t*, uint8_t);

// no simd, sub constant, 8 bits per channel, no pipeline
void sub_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_SIMDIP_SUB_H_
