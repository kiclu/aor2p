#include<simdip/max.h>

/*
OP_MAX
replace every pixel of image with maximum its value and constant
*/

static inline uint8_t max(uint8_t a, uint8_t b){ return a > b ? a : b; }

// simd, max, 8 bits per channel, no pipeline
void simd_max_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];

        size_t j = 0;
        for(; j < (imgfile->width & ~0x1F); j += 32){
            //simd_max_8bpc(ptr_r + j, ptr_g + j, ptr_b + j, c);
        }

        for(; j < imgfile->width; ++j){
            ptr_r[j] = max(ptr_r[j], c);
            ptr_g[j] = max(ptr_g[j], c);
            ptr_b[j] = max(ptr_b[j], c);
        }
    }
}

// no simd, max, 8 bits per channel, no pipeline
void max_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            imgfile->imgdata._8bpc.r[i][j] = max(imgfile->imgdata._8bpc.r[i][j], c);
            imgfile->imgdata._8bpc.g[i][j] = max(imgfile->imgdata._8bpc.g[i][j], c);
            imgfile->imgdata._8bpc.b[i][j] = max(imgfile->imgdata._8bpc.b[i][j], c);
        }
    }
}
