#ifndef _AOR2P_SIMDIP_SUBIS_H_
#define _AOR2P_SIMDIP_SUBIS_H_

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_SUBIS
subtract every pixel from constant, saturate at 0
*/

// simd, subtract constant from pixel, 8 bits per channel, pipeline
void simd_subis_8bpc(uint8_t*, uint8_t*, uint8_t*, uint8_t);

// simd, subtract constant from pixel, 8 bits per channel, no pipeline
void simd_subis_8bpc_npl(imgfile_t*, uint8_t);

// no simd, subtract constant from pixel, 8 bits per channel, no pipeline
void subis_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_SIMDIP_SUBIS_H_
