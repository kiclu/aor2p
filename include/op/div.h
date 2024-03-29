#ifndef _AOR2P_OP_DIV_H_
#define _AOR2P_OP_DIV_H_

#include<stdint.h>

#include<hw/imm.h>
#include<img/imgfile.h>

/*
OP_DIV
divide every pixel in the image by constant
*/

#ifdef  __AVX512__
extern void avx512_div_8bpc(uint8_t c);
#endif//__AVX512__

extern void avx2_div_8bpc(uint8_t c);

// simd, divide by constant, 8 bits per channel, no pipeline
void simd_div_8bpc_npl(imgfile_t*, uint8_t);

// no simd, divide by constant, 8 bits per channel, no pipeline
void div_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_OP_DIV_H_
