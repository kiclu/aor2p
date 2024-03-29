#ifndef _AOR2P_OP_SUBI_H_
#define _AOR2P_OP_SUBI_H_

#include<stdint.h>

#include<hw/imm.h>
#include<img/imgfile.h>

/*
OP_SUBI
subtract every pixel in image from constant
*/

#ifdef  __AVX512__
extern void avx512_subi_8bpc(uint8_t c);
#endif//__AVX512__

extern void avx2_subi_8bpc(uint8_t c);

// simd, sub from constant, 8 bits per channel, no pipeline
void simd_subi_8bpc_npl(imgfile_t*, uint8_t);

// no simd, sub from constant, 8 bits per channel, no pipeline
void subi_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_OP_SUBI_H_
