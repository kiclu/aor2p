#include<simdip/sub.h>

/*
OP_SUB
subtract a constant from every pixel in the image
*/

// simd, sub constant, 8 bits per channel, no pipeline
void simd_sub_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];

        size_t j = 0;
        for(; j < (imgfile->width & ~0x1F); j += 32){
            //simd_sub_8bpc(ptr_r + j, ptr_g + j, ptr_b + j, c);
        }

        for(; j < imgfile->width; ++j){
            ptr_r[j] -= c;
            ptr_g[j] -= c;
            ptr_b[j] -= c;
        }
    }
}

// no simd, sub constant, 8 bits per channel, no pipeline
void sub_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(uint32_t i = 0; i < imgfile->height; ++i){
        for(uint32_t j = 0; j < imgfile->width; ++j){
            imgfile->imgdata._8bpc.r[i][j] -= c;
            imgfile->imgdata._8bpc.g[i][j] -= c;
            imgfile->imgdata._8bpc.b[i][j] -= c;
        }
    }
}
