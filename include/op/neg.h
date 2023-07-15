#ifndef _AOR2P_OP_NEG_H_
#define _AOR2P_OP_NEG_H_

/*
OP_NEG
apply negative effect to image
*/

#ifdef  __AVX512BW__
extern void avx512_neg_8bpc();
#else
extern void avx2_neg_8bpc();
#endif//__AVX512BW__

#include<op/subi.h>

// simd, negative, 8 bits per channel, no pipeline
inline void simd_neg_8bpc_npl(imgfile_t* imgfile){ simd_subi_8bpc_npl(imgfile, 0xFF); }

// no simd, negative, 8 bits per channel, no pipeline
inline void neg_8bpc_npl(imgfile_t* imgfile){ subi_8bpc_npl(imgfile, 0xFF); }

#endif//_AOR2P_OP_NEG_H_
