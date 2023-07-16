#ifndef _AOR2P_OP_ADDS_H_
#define _AOR2P_OP_ADDS_H_

#include<stdint.h>

#include<hw/imm.h>
#include<img/imgfile.h>

/*
OP_ADDS
add a constant to every pixel in the image, saturate at 255
*/

#ifdef  __AVX512__
extern void avx512_adds_8bpc(uint8_t c);
#endif//__AVX512__

extern void avx2_adds_8bpc(uint8_t c);

// simd, add constant, 8 bits per channel, no pipeline
void simd_adds_8bpc_npl(imgfile_t*, uint8_t);

// no simd, add constant, 8 bits per channel, no pipeline
void adds_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2_OP_ADDS_H_
