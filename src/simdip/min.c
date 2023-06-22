#include<simdip/min.h>

/*
OP_MIN
replace every pixel of image with minimum its value and constant
*/

// cmpgt
// dst[i+15:i] := ( a[i+15:i] > b[i+15:i] ) ? 0xFFFF : 0

// simd, min, 8 bits per channel, pipeline
void simd_min_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, uint8_t c){
    __m256i vres_r = _mm256_min_epu8(_mm256_load_si256((__m256i*)ptr_r), _mm256_set1_epi8(c));
    __m256i vres_g = _mm256_min_epu8(_mm256_load_si256((__m256i*)ptr_g), _mm256_set1_epi8(c));
    __m256i vres_b = _mm256_min_epu8(_mm256_load_si256((__m256i*)ptr_b), _mm256_set1_epi8(c));
    _mm256_store_si256((__m256i*)ptr_r, vres_r);
    _mm256_store_si256((__m256i*)ptr_g, vres_g);
    _mm256_store_si256((__m256i*)ptr_b, vres_b);
}

static inline uint8_t min(uint8_t a, uint8_t b){ return a < b ? a : b; }

// simd, min, 8 bits per channel, no pipeline
void simd_min_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];

        size_t j = 0;
        for(; j < (imgfile->width & ~0x1F); j += 32){
            simd_min_8bpc(ptr_r + j, ptr_g + j, ptr_b + j, c);
        }

        for(; j < imgfile->width; ++j){
            ptr_r[j] = min(ptr_r[j], c);
            ptr_g[j] = min(ptr_g[j], c);
            ptr_b[j] = min(ptr_b[j], c);
        }
    }
}

// no simd, min, 8 bits per channel, no pipeline
void min_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            imgfile->imgdata._8bpc.r[i][j] = min(imgfile->imgdata._8bpc.r[i][j], c);
            imgfile->imgdata._8bpc.g[i][j] = min(imgfile->imgdata._8bpc.g[i][j], c);
            imgfile->imgdata._8bpc.b[i][j] = min(imgfile->imgdata._8bpc.b[i][j], c);
        }
    }
}
