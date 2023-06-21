#include<simdip/mul.h>

/*
OP_MUL
multiply every pixel of image by constant
*/

// simd, multiply by constant, .bmp, 8 bits per channel, pipeline
void simd_mul_bmp_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, uint8_t c){
    __m256 va_r[4] = {
        _mm256_setr_ps(ptr_r[0],  ptr_r[1],  ptr_r[2],  ptr_r[3],  ptr_r[16], ptr_r[17], ptr_r[18], ptr_r[19]),
        _mm256_setr_ps(ptr_r[4],  ptr_r[5],  ptr_r[6],  ptr_r[7],  ptr_r[20], ptr_r[21], ptr_r[22], ptr_r[23]),
        _mm256_setr_ps(ptr_r[8],  ptr_r[9],  ptr_r[10], ptr_r[11], ptr_r[24], ptr_r[25], ptr_r[26], ptr_r[27]),
        _mm256_setr_ps(ptr_r[12], ptr_r[13], ptr_r[14], ptr_r[15], ptr_r[28], ptr_r[29], ptr_r[30], ptr_r[31])
    };

    __m256 va_g[4] = {
        _mm256_setr_ps(ptr_g[0],  ptr_g[1],  ptr_g[2],  ptr_g[3],  ptr_g[16], ptr_g[17], ptr_g[18], ptr_g[19]),
        _mm256_setr_ps(ptr_g[4],  ptr_g[5],  ptr_g[6],  ptr_g[7],  ptr_g[20], ptr_g[21], ptr_g[22], ptr_g[23]),
        _mm256_setr_ps(ptr_g[8],  ptr_g[9],  ptr_g[10], ptr_g[11], ptr_g[24], ptr_g[25], ptr_g[26], ptr_g[27]),
        _mm256_setr_ps(ptr_g[12], ptr_g[13], ptr_g[14], ptr_g[15], ptr_g[28], ptr_g[29], ptr_g[30], ptr_g[31])
    };

    __m256 va_b[4] = {
        _mm256_setr_ps(ptr_b[0],  ptr_b[1],  ptr_b[2],  ptr_b[3],  ptr_b[16], ptr_b[17], ptr_b[18], ptr_b[19]),
        _mm256_setr_ps(ptr_b[4],  ptr_b[5],  ptr_b[6],  ptr_b[7],  ptr_b[20], ptr_b[21], ptr_b[22], ptr_b[23]),
        _mm256_setr_ps(ptr_b[8],  ptr_b[9],  ptr_b[10], ptr_b[11], ptr_b[24], ptr_b[25], ptr_b[26], ptr_b[27]),
        _mm256_setr_ps(ptr_b[12], ptr_b[13], ptr_b[14], ptr_b[15], ptr_b[28], ptr_b[29], ptr_b[30], ptr_b[31])
    };

    __m256i vres_r = _mm256_packus_epi16(
        _mm256_packus_epi32(
            _mm256_cvtps_epi32(_mm256_mul_ps(va_r[0], _mm256_set1_ps(c))),
            _mm256_cvtps_epi32(_mm256_mul_ps(va_r[1], _mm256_set1_ps(c)))
        ),
        _mm256_packus_epi32(
            _mm256_cvtps_epi32(_mm256_mul_ps(va_r[2], _mm256_set1_ps(c))),
            _mm256_cvtps_epi32(_mm256_mul_ps(va_r[3], _mm256_set1_ps(c)))
        )
    );
    
    __m256i vres_g = _mm256_packus_epi16(
        _mm256_packus_epi32(
            _mm256_cvtps_epi32(_mm256_mul_ps(va_g[0], _mm256_set1_ps(c))),
            _mm256_cvtps_epi32(_mm256_mul_ps(va_g[1], _mm256_set1_ps(c)))
        ),
        _mm256_packus_epi32(
            _mm256_cvtps_epi32(_mm256_mul_ps(va_g[2], _mm256_set1_ps(c))),
            _mm256_cvtps_epi32(_mm256_mul_ps(va_g[3], _mm256_set1_ps(c)))
        )
    );

    __m256i vres_b = _mm256_packus_epi16(
        _mm256_packus_epi32(
            _mm256_cvtps_epi32(_mm256_mul_ps(va_b[0], _mm256_set1_ps(c))),
            _mm256_cvtps_epi32(_mm256_mul_ps(va_b[1], _mm256_set1_ps(c)))
        ),
        _mm256_packus_epi32(
            _mm256_cvtps_epi32(_mm256_mul_ps(va_b[2], _mm256_set1_ps(c))),
            _mm256_cvtps_epi32(_mm256_mul_ps(va_b[3], _mm256_set1_ps(c)))
        )
    );

    _mm256_store_si256((__m256i*)ptr_r, vres_r);
    _mm256_store_si256((__m256i*)ptr_g, vres_g);
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
