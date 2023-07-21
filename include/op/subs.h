#ifndef _AOR2P_OP_SUBS_H_
#define _AOR2P_OP_SUBS_H_

#include<stdint.h>

#include<hw/imm.h>
#include<img/imgfile.h>

/*
OP_SUBS
subtract constant from every pixel in the image, saturate at 0
*/

#ifdef  __AVX512__
extern void avx512_subs_8bpc(uint8_t c);
#endif//__AVX512__

extern void avx2_subs_8bpc(uint8_t c);

// simd, subtract constant from pixel, 8 bits per channel, no pipeline
void simd_subs_8bpc_npl(imgfile_t*, uint8_t);

// no simd, subtract constant from pixel, 8 bits per channel, no pipeline
void subs_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_OP_SUBS_H_
