#include<simdip/div.h>

/*
OP_DIVI
divide constant by every pixel in the image
*/

// simd, divide constant by pixel, .bmp, 8 bits per channel, pipeline
void simd_divi_bmp_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, uint8_t c){
    for(uint32_t k = 0; k < 32; k += 8){
        __m256 fva_r = _mm256_cvtepi32_ps(
            _mm256_setr_epi32(
                ptr_r[k+0], ptr_r[k+1], ptr_r[k+2], ptr_r[k+3],
                ptr_r[k+4], ptr_r[k+5], ptr_r[k+6], ptr_r[k+7]
            )
        );
        __m256i vres_r = _mm256_cvtps_epi32(_mm256_div_ps(_mm256_set1_ps(c), fva_r));

        __m256 fva_g = _mm256_cvtepi32_ps(
            _mm256_setr_epi32(
                ptr_g[k+0], ptr_g[k+1], ptr_g[k+2], ptr_g[k+3],
                ptr_g[k+4], ptr_g[k+5], ptr_g[k+6], ptr_g[k+7]
            )
        );
        __m256i vres_g = _mm256_cvtps_epi32(_mm256_div_ps(_mm256_set1_ps(c), fva_g));

        __m256 fva_b = _mm256_cvtepi32_ps(
            _mm256_setr_epi32(
                ptr_b[k+0], ptr_b[k+1], ptr_b[k+2], ptr_b[k+3],
                ptr_b[k+4], ptr_b[k+5], ptr_b[k+6], ptr_b[k+7]
            )
        );
        __m256i vres_b = _mm256_cvtps_epi32(_mm256_div_ps(_mm256_set1_ps(c), fva_b));

        for(size_t i = 0; i < 8; ++i){
            ptr_r[k+i] = *((uint8_t*)&vres_r + (i << 2));
            ptr_g[k+i] = *((uint8_t*)&vres_g + (i << 2));
            ptr_b[k+i] = *((uint8_t*)&vres_b + (i << 2));
        }
    }
}

static inline uint8_t _divi(uint8_t a, uint8_t b){
    return b ? a / b : 0;
}

// simd, divide constant by pixel, .bmp, 8 bits per channel, no pipeline
void simd_divi_bmp_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];

        size_t j = 0;
        for(j = 0; j < (imgfile->width & ~0x1F); j += 32){
            simd_div_bmp_8bpc(ptr_r, ptr_b, ptr_g, c);
        }

        for(; j < imgfile->width; ++j){
            ptr_r[j] = _divi(c, ptr_r[j]);
            ptr_g[j] = _divi(c, ptr_g[j]);
            ptr_b[j] = _divi(c, ptr_b[j]);
        }
    }
}

// no simd, divide constant by pixel, .bmp, 8 bits per channel, no pipeline
void divi_bmp_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            imgfile->imgdata._8bpc.r[i][j] = _divi(c, imgfile->imgdata._8bpc.r[i][j]);
            imgfile->imgdata._8bpc.g[i][j] = _divi(c, imgfile->imgdata._8bpc.g[i][j]);
            imgfile->imgdata._8bpc.b[i][j] = _divi(c, imgfile->imgdata._8bpc.b[i][j]);
        }
    }
}
