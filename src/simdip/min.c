#include<simdip/min.h>

/*
OP_MIN
replace every pixel of image with minimum its value and constant
*/

// simd, min, .bmp, 8 bits per channel, pipeline
void simd_min_bmp_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, uint8_t c){

}

// simd, min, .bmp, 8 bits per channel, no pipeline
void simd_min_bmp_8bpc_npl(imgfile_t* imgfile, uint8_t c){

}

// no simd, min, .bmp, 8 bits per channel, no pipeline
void min_bmp_8bpc_npl(imgfile_t* imgfile, uint8_t c){

}
