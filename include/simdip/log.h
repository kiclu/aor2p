#ifndef _AOR2P_SIMDIP_LOG_H_
#define _AOR2P_SIMDIP_LOG_H_

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_LOG
replace every pixel of image with its logarithm
*/

#ifdef  __AVX512BW__

extern void avx512_log_8bpc(uint8_t c);
#define simd_log_8bpc(c) avx512_log_8bpc(c)

#else

extern void avx2_log_8bpc(uint8_t c);
#define simd_log_8bpc(c) avx2_log_8bpc(c)

#endif//__AVX512BW__

// simd, log, 8 bits per channel, no pipeline
void simd_log_8bpc_npl(imgfile_t*);

// no simd, log, 8 bits per channel, no pipeline
void log_8bpc_npl(imgfile_t*);

#endif//_AOR2P_SIMDIP_LOG_H_
