#include<simdip/subi.h>

/*
OP_SUBI
subtract every pixel in image from constant
*/

// simd, sub from constant, .bmp, 8 bits per channel, pipeline
void simd_subi_bmp_8bpc(__m256i* ptr_r, __m256i* ptr_g, __m256i* ptr_b, uint8_t c){
    __m256i vc = _mm256_set1_epi8(c);
    __m256i va_r = _mm256_load_si256(ptr_r);
    __m256i va_g = _mm256_load_si256(ptr_g);
    __m256i va_b = _mm256_load_si256(ptr_b);
    _mm256_store_si256(ptr_r, _mm256_sub_epi8(vc, va_r));
    _mm256_store_si256(ptr_g, _mm256_sub_epi8(vc, va_g));
    _mm256_store_si256(ptr_b, _mm256_sub_epi8(vc, va_b));
}

#include<stdio.h>

// simd, sub from constant, .bmp, 8 bits per channel, no pipeline
void simd_subi_bmp_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    printf("simd_sub_bmp_8bpc_npp\n");

    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];
        size_t j = 0;
        for(; j < (imgfile->width & ~0x1F); j += 32, ptr_r += 32, ptr_g += 32, ptr_b += 32){
            simd_subi_bmp_8bpc(
                (__m256i*)ptr_r,
                (__m256i*)ptr_g,
                (__m256i*)ptr_b,
                c
            );
        }
        for(; j < imgfile->width; ++j){
            *ptr_r++ = c - *ptr_r;
            *ptr_g++ = c - *ptr_g;
            *ptr_b++ = c - *ptr_b;
        }
    }
}

// no simd, sub from constant, .bmp, 8 bits per channel, no pipeline
void subi_bmp_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    printf("sub_bmp_8bpc_npp\n");
    for(uint32_t i = 0; i < imgfile->height; ++i){
        for(uint32_t j = 0; j < imgfile->width; ++j){
            // TODO: implement
        }
    }
}
