#ifndef _AOR2P_OP_MUL_H_
#define _AOR2P_OP_MUL_H_

#include<img/imgfile.h>

/*
OP_MUL
multiply every pixel of image by constant
*/

#ifdef  __AVX512BW__
extern void avx512_mul_8bpc(uint8_t c);
#else
extern void avx2_mul_8bpc(uint8_t c);
#endif//__AVX512BW__

// simd, multiply by constant, 8 bits per channel, no pipeline
void simd_mul_8bpc_npl(imgfile_t*, uint8_t);

// no simd, multiply by constant, 8 bits per channel, no pipeline
void mul_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_OP_MUL_H_
