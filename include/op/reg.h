#ifndef _AOR2P_OP_REG_H_
#define _AOR2P_OP_REG_H_

#include<stdint.h>

#ifdef  __AVX512F__

extern void avx512_reg_load_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b);
#define simd_reg_load_8bpc(ptr_r, ptr_g, ptr_b) avx512_reg_load_8bpc(ptr_r, ptr_g, ptr_b)

extern void avx512_reg_store_8pbc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b);
#define simd_reg_store_8bpc(ptr_r, ptr_g, ptr_b) avx512_reg_store_8bpc(ptr_r, ptr_g, ptr_b);

#else

extern void avx2_reg_load_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b);
#define simd_reg_load_8bpc(ptr_r, ptr_g, ptr_b) avx2_reg_load_8bpc(ptr_r, ptr_g, ptr_b);

extern void avx2_reg_store_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b);
#define simd_reg_store_8bpc(ptr_r, ptr_g, ptr_b) avx2_reg_store_8bpc(ptr_r, ptr_g, ptr_b);

#endif//__AVX512F__

#endif//_AOR2P_OP_REG_H_
