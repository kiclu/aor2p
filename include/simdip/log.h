#ifndef _SIMDIP_LOG_H
#define _SIMDIP_LOG_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_LOG
replace every pixel of image with its logarithm
*/

// simd, log, .bmp, 8 bits per channel, pipeline
void simd_log_bmp_8bpc(uint8_t*, uint8_t*, uint8_t*);

// simd, log, .bmp, 8 bits per channel, no pipeline
void simd_log_bmp_8bpc_npl(imgfile_t*);

// no simd, log, .bmp, 8 bits per channel, no pipeline
void log_bmp_8bpc_npl(imgfile_t*);

#endif//_SIMDIP_LOG_H
