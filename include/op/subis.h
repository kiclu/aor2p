#ifndef _AOR2P_OP_SUBIS_H_
#define _AOR2P_OP_SUBIS_H_

#include<stdint.h>

#include<hw/imm.h>
#include<img/imgfile.h>

/*
OP_SUBIS
subtract every pixel from constant, saturate at 0
*/

#ifdef  __AVX512__
extern void avx512_subis_8bpc(uint8_t c);
#endif//__AVX512__

extern void avx2_subis_8bpc(uint8_t c);

// simd, subtract constant from pixel, 8 bits per channel, no pipeline
void simd_subis_8bpc_npl(imgfile_t*, uint8_t);

// no simd, subtract constant from pixel, 8 bits per channel, no pipeline
void subis_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_OP_SUBIS_H_
