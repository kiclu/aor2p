#include<simdip/abs.h>

/*
OP_ABS
absolute value of every pixel in the image
*/

// simd, absolute value, 8 bits per channel, pipeline
void simd_abs_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b){
    __m256i va_r = _mm256_load_si256((__m256i*)ptr_r);
    __m256i va_g = _mm256_load_si256((__m256i*)ptr_g);
    __m256i va_b = _mm256_load_si256((__m256i*)ptr_b);
    _mm256_store_si256((__m256i*)ptr_r, _mm256_abs_epi8(va_r));
    _mm256_store_si256((__m256i*)ptr_g, _mm256_abs_epi8(va_g));
    _mm256_store_si256((__m256i*)ptr_b, _mm256_abs_epi8(va_b));
}

inline static int8_t _abs(int8_t x){ return x >= 0 ? x : -x; }

// simd, absolute value, 8 bits per channel, no pipeline
void simd_abs_8bpc_npl(imgfile_t* imgfile){
    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];

        size_t j = 0;
        for(; j < (imgfile->width & ~0x1F); j += 32){
            simd_abs_8bpc(ptr_r + j, ptr_g + j, ptr_b + j);
        }

        for(; j < imgfile->width; ++j){
            ptr_r[j] = _abs(ptr_r[j]);
            ptr_g[j] = _abs(ptr_g[j]);
            ptr_b[j] = _abs(ptr_b[j]);
        }
    }
}

// no simd, absolute value, 8 bits per channel, no pipeline
void abs_8bpc_npl(imgfile_t* imgfile){
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            imgfile->imgdata._8bpc.r[i][j] = _abs(imgfile->imgdata._8bpc.r[i][j]);
            imgfile->imgdata._8bpc.g[i][j] = _abs(imgfile->imgdata._8bpc.g[i][j]);
            imgfile->imgdata._8bpc.b[i][j] = _abs(imgfile->imgdata._8bpc.b[i][j]);
        }
    }
}
