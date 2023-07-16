#ifndef _AOR2P_OP_LOG_H_
#define _AOR2P_OP_LOG_H_

#include<stdint.h>

#include<hw/imm.h>
#include<img/imgfile.h>

/*
OP_LOG
replace every pixel of image with its logarithm
*/

#ifdef  __AVX512__
extern void avx512_log_8bpc(uint8_t c);
#endif//__AVX512__

extern void avx2_log_8bpc(uint8_t c);

// simd, log, 8 bits per channel, no pipeline
void simd_log_8bpc_npl(imgfile_t*);

// no simd, log, 8 bits per channel, no pipeline
void log_8bpc_npl(imgfile_t*);

#endif//_AOR2P_OP_LOG_H_
