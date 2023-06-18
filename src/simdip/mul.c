#include<simdip/mul.h>

/*
OP_MUL
multiply every pixel of image by constant
*/

// simd, multiply by constant, .bmp, 8 bits per channel, pipeline
void simd_mul_bmp_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, uint8_t c){

}

// simd, multiply by constant, .bmp, 8 bits per channel, no pipeline
void simd_mul_bmp_8bpc_npl(imgfile_t* filename, uint8_t c){
    
}

// no simd, multiply by constant, .bmp, 8 bits per channel, no pipeline
void mul_bmp_8bpc_npl(imgfile_t* filename, uint8_t c){

}
