#include<simdip/subs.h>

/*
OP_SUBS
subtract constant from every pixel in the image, saturate at 0
*/

// simd, subtract constant from pixel, 8 bits per channel, no pipeline
void simd_subs_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];

        size_t j = 0;
        for(; j < (imgfile->width & ~0x1F); j += 32){
            // simd_subs_8bpc(ptr_r + j, ptr_g + j, ptr_b + j, c);
        }

        for(; j < imgfile->width; ++j){
            ptr_r[j] = ptr_r[j] - c < 0 ? 0 : ptr_r[j] - c;
            ptr_g[j] = ptr_g[j] - c < 0 ? 0 : ptr_g[j] - c;
            ptr_b[j] = ptr_b[j] - c < 0 ? 0 : ptr_b[j] - c;
        }
    }
}

// no simd, subtract constant from pixel, 8 bits per channel, no pipeline
void subs_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            uint8_t r = imgfile->imgdata._8bpc.r[i][j];
            uint8_t g = imgfile->imgdata._8bpc.g[i][j];
            uint8_t b = imgfile->imgdata._8bpc.b[i][j];
            imgfile->imgdata._8bpc.r[i][j] = r - c < 0 ? 0 : r - c;
            imgfile->imgdata._8bpc.g[i][j] = g - c < 0 ? 0 : g - c;
            imgfile->imgdata._8bpc.b[i][j] = b - c < 0 ? 0 : b - c;
        }
    }
}

