#include<simdip/mul.h>

/*
OP_MUL
multiply every pixel of image by constant
*/

// simd, multiply by constant, .bmp, 8 bits per channel, pipeline
void simd_mul_bmp_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, uint8_t c){
    __m256i va_r[] = {
        _mm256_inserti128_si256(
            _mm256_castsi128_si256(_mm_cvtepu8_epi16(_mm_loadu_si128((__m128i*)ptr_r))),
            _mm_cvtepu8_epi16(_mm_loadu_si128((__m128i*)(ptr_r + 16))), 1
        ),
        _mm256_inserti128_si256(
            _mm256_castsi128_si256(_mm_cvtepu8_epi16(_mm_loadu_si128((__m128i*)(ptr_r + 8)))),
            _mm_cvtepu8_epi16(_mm_loadu_si128((__m128i*)(ptr_r + 24))), 1
        )
    };
    __m256i vres_r = _mm256_packus_epi16(
        _mm256_mullo_epi16(va_r[0], _mm256_set1_epi16(c)),
        _mm256_mullo_epi16(va_r[1], _mm256_set1_epi16(c))
    );
    _mm256_store_si256((__m256i*)ptr_r, vres_r);

    __m256i va_g[] = {
        _mm256_inserti128_si256(
            _mm256_castsi128_si256(_mm_cvtepu8_epi16(_mm_loadu_si128((__m128i*)ptr_g))),
            _mm_cvtepu8_epi16(_mm_loadu_si128((__m128i*)(ptr_g + 16))), 1
        ),
        _mm256_inserti128_si256(
            _mm256_castsi128_si256(_mm_cvtepu8_epi16(_mm_loadu_si128((__m128i*)(ptr_g + 8)))),
            _mm_cvtepu8_epi16(_mm_loadu_si128((__m128i*)(ptr_g + 24))), 1
        )
    };
    __m256i vres_g = _mm256_packus_epi16(
        _mm256_mullo_epi16(va_g[0], _mm256_set1_epi16(c)),
        _mm256_mullo_epi16(va_g[1], _mm256_set1_epi16(c))
    );
    _mm256_store_si256((__m256i*)ptr_g, vres_g);

    __m256i va_b[] = {
        _mm256_inserti128_si256(
            _mm256_castsi128_si256(_mm_cvtepu8_epi16(_mm_loadu_si128((__m128i*)ptr_b))),
            _mm_cvtepu8_epi16(_mm_loadu_si128((__m128i*)(ptr_b + 16))), 1
        ),
        _mm256_inserti128_si256(
            _mm256_castsi128_si256(_mm_cvtepu8_epi16(_mm_loadu_si128((__m128i*)(ptr_b + 8)))),
            _mm_cvtepu8_epi16(_mm_loadu_si128((__m128i*)(ptr_b + 24))), 1
        )
    };
    __m256i vres_b = _mm256_packus_epi16(
        _mm256_mullo_epi16(va_b[0], _mm256_set1_epi16(c)),
        _mm256_mullo_epi16(va_b[1], _mm256_set1_epi16(c))
    );
    _mm256_store_si256((__m256i*)ptr_b, vres_b);
}

// simd, multiply by constant, .bmp, 8 bits per channel, no pipeline
void simd_mul_bmp_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];

        size_t j = 0;
        for(j = 0; j < (imgfile->width & ~0x1F); j += 32){
            simd_mul_bmp_8bpc(ptr_r, ptr_b, ptr_g, c);
        }

        for(; j < imgfile->width; ++j){
            ptr_r[j] *= c;
            ptr_g[j] *= c;
            ptr_b[j] *= c;
        }
    }
}

// no simd, multiply by constant, .bmp, 8 bits per channel, no pipeline
void mul_bmp_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            imgfile->imgdata._8bpc.r[i][j] *= c;
            imgfile->imgdata._8bpc.g[i][j] *= c;
            imgfile->imgdata._8bpc.b[i][j] *= c;
        }
    }
}
