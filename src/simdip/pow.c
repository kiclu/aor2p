#include<simdip/pow.h>

/*
OP_POW
raise every pixel of image to power of constant
*/

// simd, pow, .bmp, 8 bits per channel, pipeline
void simd_pow_bmp_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, uint8_t c){

}

// simd, pow, .bmp, 8 bits per channel, no pipeline
void simd_pow_bmp_8bpc_npl(imgfile_t* imgfile, uint8_t c){

}

// no simd, pow, .bmp, 8 bits per channel, no pipeline
void pow_bmp_8bpc_npl(imgfile_t* imgfile, uint8_t c){

}
