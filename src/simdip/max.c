#include<simdip/max.h>

/*
OP_MAX
replace every pixel of image with maximum its value and constant
*/

// simd, max, .bmp, 8 bits per channel, pipeline
void simd_max_bmp_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, uint8_t c){
    // __m256i va_r = _mm256_load_si256((__m256i*)ptr_r);
    // __m256i va_g = _mm256_load_si256((__m256i*)ptr_g);
    // __m256i va_b = _mm256_load_si256((__m256i*)ptr_b);
    // __m256i vc = _mm256_set1_epi8(c);
    // __m256i vm;

    

}

// simd, max, .bmp, 8 bits per channel, no pipeline
void simd_max_bmp_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];

        size_t j = 0;
        for(; j < (imgfile->width & ~0x1F); j += 32){
            simd_max_bmp_8bpc(ptr_r + j, ptr_g + j, ptr_b + j, c);
        }

        for(; j < imgfile->width; ++j){
            *ptr_r++ = *ptr_r > c ? *ptr_r : c;
            *ptr_g++ = *ptr_g > c ? *ptr_g : c;
            *ptr_b++ = *ptr_b > c ? *ptr_b : c;
        }
    }
}

// no simd, max, .bmp, 8 bits per channel, no pipeline
void max_bmp_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            uint8_t r = imgfile->imgdata._8bpc.r[i][j];
            uint8_t g = imgfile->imgdata._8bpc.g[i][j];
            uint8_t b = imgfile->imgdata._8bpc.b[i][j];

            imgfile->imgdata._8bpc.r[i][j] = r > c ? r : c;
            imgfile->imgdata._8bpc.g[i][j] = g > c ? g : c;
            imgfile->imgdata._8bpc.b[i][j] = b > c ? b : c;
        }
    }
}
