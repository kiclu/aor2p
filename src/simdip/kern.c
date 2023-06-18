#include<simdip/kern.h>

/*
OP_KERN
apply kernel to image
*/

// simd, apply kernel to pixel, .bmp, 8 bits per channel, pipeline
void simd_kern_bmp_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, kern_t k){

}

// simd, apply kernel to pixel, .bmp, 8 bits per channel, no pipeline
void simd_kern_bmp_8bpc_npl(imgfile_t* imgfile, kern_t k){

}

// no simd, apply kernel to pixel, .bmp, 8 bits per channel, no pipeline
void kern_bmp_8bpc_npl(imgfile_t* imgfile, kern_t k){

}
