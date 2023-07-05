#include<simdip/mul.h>

/*
OP_MUL
multiply every pixel of image by constant
*/

// simd, multiply by constant, 8 bits per channel, no pipeline
void simd_mul_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];

        size_t j = 0;
        for(j = 0; j < (imgfile->width & ~0x1F); j += 32){
            // simd_mul_8bpc(ptr_r, ptr_b, ptr_g, c);
        }

        for(; j < imgfile->width; ++j){
            ptr_r[j] *= c;
            ptr_g[j] *= c;
            ptr_b[j] *= c;
        }
    }
}

inline uint8_t muls_8bpc(uint8_t a, uint8_t c){
    if(a * c >= 0xFF) return 0xFF;
    return a * c;
}

// no simd, multiply by constant, 8 bits per channel, no pipeline
void mul_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            imgfile->imgdata._8bpc.r[i][j] = muls_8bpc(imgfile->imgdata._8bpc.r[i][j], c);
            imgfile->imgdata._8bpc.g[i][j] = muls_8bpc(imgfile->imgdata._8bpc.g[i][j], c);
            imgfile->imgdata._8bpc.b[i][j] = muls_8bpc(imgfile->imgdata._8bpc.b[i][j], c);
        }
    }
}
