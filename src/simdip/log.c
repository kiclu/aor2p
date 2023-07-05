#include<simdip/log.h>

/*
OP_LOG
replace every pixel of image with its logarithm
*/

// https://en.wikipedia.org/wiki/Fast_inverse_square_root

#include<math.h>

static inline int log2i(int x){ return log(x) / log(2); }

// simd, log, 8 bits per channel, no pipeline
void simd_log_8bpc_npl(imgfile_t* imgfile){
    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];

        size_t j = 0;
        for(j = 0; j < (imgfile->width & ~0x1F); j += 32){
            // simd_log_8bpc(ptr_r, ptr_g, ptr_b);
        }

        for(; j < imgfile->width; ++j){
            ptr_r[j] = log2i(ptr_r[j]);
            ptr_g[j] = log2i(ptr_g[j]);
            ptr_b[j] = log2i(ptr_b[j]);
        }
    }
}

// no simd, log, 8 bits per channel, no pipeline
void log_8bpc_npl(imgfile_t* imgfile){
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            imgfile->imgdata._8bpc.r[i][j] = log2i(imgfile->imgdata._8bpc.r[i][j]);
            imgfile->imgdata._8bpc.g[i][j] = log2i(imgfile->imgdata._8bpc.g[i][j]);
            imgfile->imgdata._8bpc.b[i][j] = log2i(imgfile->imgdata._8bpc.b[i][j]);
        }
    }
}
