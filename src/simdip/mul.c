#include<simdip/mul.h>

/*
OP_MUL
multiply every pixel of image by constant
*/

// simd, multiply by constant, .bmp, 8 bits per channel, pipeline
void simd_mul_bmp_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, uint8_t c){
    for(uint32_t k = 0; k < 32; k += 8){
        __m256 fva_r = _mm256_cvtepi32_ps(
            _mm256_setr_epi32(
                ptr_r[k+0], ptr_r[k+1], ptr_r[k+2], ptr_r[k+3],
                ptr_r[k+4], ptr_r[k+5], ptr_r[k+6], ptr_r[k+7]
            )
        );
        __m256i vres_r = _mm256_cvtps_epi32(_mm256_mul_ps(fva_r, _mm256_set1_ps(c)));

        __m256 fva_g = _mm256_cvtepi32_ps(
            _mm256_setr_epi32(
                ptr_g[k+0], ptr_g[k+1], ptr_g[k+2], ptr_g[k+3],
                ptr_g[k+4], ptr_g[k+5], ptr_g[k+6], ptr_g[k+7]
            )
        );
        __m256i vres_g = _mm256_cvtps_epi32(_mm256_mul_ps(fva_g, _mm256_set1_ps(c)));

        __m256 fva_b = _mm256_cvtepi32_ps(
            _mm256_setr_epi32(
                ptr_b[k+0], ptr_b[k+1], ptr_b[k+2], ptr_b[k+3],
                ptr_b[k+4], ptr_b[k+5], ptr_b[k+6], ptr_b[k+7]
            )
        );
        __m256i vres_b = _mm256_cvtps_epi32(_mm256_mul_ps(fva_b, _mm256_set1_ps(c)));

        for(size_t i = 0; i < 8; ++i){
            ptr_r[k+i] = *((uint8_t*)&vres_r + (i << 2));
            ptr_g[k+i] = *((uint8_t*)&vres_g + (i << 2));
            ptr_b[k+i] = *((uint8_t*)&vres_b + (i << 2));
        }
    }
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
