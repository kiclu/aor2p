#ifndef _AOR2P_OP_DIVI_H_
#define _AOR2P_OP_DIVI_H_

#include<img/imgfile.h>

/*
OP_DIVI
divide constant by every pixel in the image
*/

#ifdef  __AVX512BW__
extern void avx512_divi_8bpc(uint8_t c);
#else
extern void avx2_divi_8bpc(uint8_t c);
#endif//__AVX512BW__

// simd, divide constant by pixel, 8 bits per channel, no pipeline
void simd_divi_8bpc_npl(imgfile_t*, uint8_t);

// no simd, divide constant by pixel, 8 bits per channel, no pipeline
void divi_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_OP_DIVI_H
