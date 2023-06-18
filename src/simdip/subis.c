#include<simdip/subis.h>

/*
OP_SUBIS
subtract every pixel from constant, saturate at 0
*/

// simd, subtract constant from pixel, .bmp, 8 bits per channel, pipeline
void simd_subis_bmp_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, uint8_t c){

}

// simd, subtract constant from pixel, .bmp, 8 bits per channel, no pipeline
void simd_subis_bmp_8bpc_npl(imgfile_t* imgfile, uint8_t c){

}

// no simd, subtract constant from pixel, .bmp, 8 bits per channel, no pipeline
void subis_bmp_8bpc_npl(imgfile_t* imgfile, uint8_t c){

}
