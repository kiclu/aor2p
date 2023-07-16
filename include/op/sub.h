#ifndef _AOR2P_OP_SUB_H_
#define _AOR2P_OP_SUB_H_

#include<stdint.h>

#include<hw/imm.h>
#include<img/imgfile.h>

/*
OP_SUB
subtract a constant from every pixel in the image
*/

#ifdef  __AVX512__
extern void avx512_sub_8bpc(uint8_t c);
#endif//__AVX512__

extern void avx2_sub_8bpc(uint8_t c);

// simd, sub constant, 8 bits per channel, no pipeline
void simd_sub_8bpc_npl(imgfile_t*, uint8_t);

// no simd, sub constant, 8 bits per channel, no pipeline
void sub_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_OP_SUB_H_
