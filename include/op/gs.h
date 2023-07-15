#ifndef _AOR2P_OP_GS_H_
#define _AOR2P_OP_GS_H_

#include<img/imgfile.h>

/*
OP_GS
convert image to grayscale
*/

#ifdef  __AVX512BW__
extern void avx512_gs_8bpc(uint8_t c);
#else
extern void avx2_gs_8bpc(uint8_t c);
#endif//__AVX512BW__

// simd, convert to grayscale, 8 bits per channel, no pipeline
void simd_gs_8bpc_npl(imgfile_t*);

// no simd, convert to grayscale, 8 bits per channel, no pipeline
void gs_8bpc_npl(imgfile_t*);

#endif//_AOR2P_OP_GS_H_
