#ifndef _AOR2P_SIMDIP_NEG_H_
#define _AOR2P_SIMDIP_NEG_H_

#include<simdip/subi.h>

/*
OP_NEG
apply negative effect to image
*/

// simd, negative, 8 bits per channel, pipeline
inline void simd_neg_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b){
    simd_subi_8bpc(ptr_r, ptr_g, ptr_b, 0xFF);
}

// simd, negative, 8 bits per channel, no pipeline
inline void simd_neg_8bpc_npl(imgfile_t* imgfile){
    simd_subi_8bpc_npl(imgfile, 0xFF);
}

// no simd, negative, 8 bits per channel, no pipeline
inline void neg_8bpc_npl(imgfile_t* imgfile){
    subi_8bpc_npl(imgfile, 0xFF);
}

#endif//_AOR2P_SIMDIP_NEG_H_
