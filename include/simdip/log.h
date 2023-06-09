#ifndef _AOR2P_SIMDIP_LOG_H_
#define _AOR2P_SIMDIP_LOG_H_

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_LOG
replace every pixel of image with its logarithm
*/

// simd, log, 8 bits per channel, pipeline
void simd_log_8bpc(uint8_t*, uint8_t*, uint8_t*);

// simd, log, 8 bits per channel, no pipeline
void simd_log_8bpc_npl(imgfile_t*);

// no simd, log, 8 bits per channel, no pipeline
void log_8bpc_npl(imgfile_t*);

#endif//_AOR2P_SIMDIP_LOG_H_
