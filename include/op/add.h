#ifndef _AOR2P_OP_ADD_H_
#define _AOR2P_OP_ADD_H_

#include<img/imgfile.h>

/*
OP_ADD
add a constant to every pixel in the image
*/

#ifdef  __AVX512BW__
extern void avx512_add_8bpc(uint8_t c);
#else
extern void avx2_add_8bpc(uint8_t c);
#endif//__AVX512BW__

// simd, add constant, 8 bits per channel, no pipeline
void simd_add_8bpc_npl(imgfile_t*, uint8_t);

// no simd, add constant, 8 bits per channel, no pipeline
void add_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_OP_ADD_H_
