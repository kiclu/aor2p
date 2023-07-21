#ifndef _AOR2P_OP_POW_H_
#define _AOR2P_OP_POW_H_

#include<stdint.h>

#include<hw/imm.h>
#include<img/imgfile.h>

/*
OP_POW
raise every pixel of image to power of constant
*/

#ifdef  __AVX512__
extern void avx512_pow_8bpc(uint8_t c);
#endif//__AVX512__

extern void avx2_pow_8bpc(uint8_t c);

// simd, pow, 8 bits per channel, no pipeline
void simd_pow_8bpc_npl(imgfile_t*, uint8_t);

// no simd, pow, 8 bits per channel, no pipeline
void pow_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_OP_POW_H_
