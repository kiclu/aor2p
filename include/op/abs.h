#ifndef _AOR2P_OP_ABS_H_
#define _AOR2P_OP_ABS_H_

#include<img/imgfile.h>

/*
OP_ABS
absolute value of every pixel in the image
*/

#ifdef  __AVX512BW__
extern void avx512_abs_8bpc(uint8_t c);
#else
extern void avx2_abs_8bpc(uint8_t c);
#endif//__AVX512BW__

// simd, absolute value, 8 bits per channel, no pipeline
void simd_abs_8bpc_npl(imgfile_t*);

// no simd, absolute value, 8 bits per channel, no pipeline
void abs_8bpc_npl(imgfile_t*);

#endif//_AOR2P_OP_ABS_H_
