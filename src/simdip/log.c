#include<simdip/log.h>

/*
OP_LOG
replace every pixel of image with its logarithm
*/

// simd, log, .bmp, 8 bits per channel, pipeline
void simd_log_bmp_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b){
    for(size_t k = 0; k < 32; k += 8){
        __m256 fva_r = _mm256_cvtepi32_ps(
            _mm256_setr_epi32(
                ptr_r[k+0], ptr_r[k+1], ptr_r[k+2], ptr_r[k+3],
                ptr_r[k+4], ptr_r[k+5], ptr_r[k+6], ptr_r[k+7]
            )
        );

        __m256 fva_g = _mm256_cvtepi32_ps(
            _mm256_setr_epi32(
                ptr_g[k+0], ptr_g[k+1], ptr_g[k+2], ptr_g[k+3],
                ptr_g[k+4], ptr_g[k+5], ptr_g[k+6], ptr_g[k+7]
            )
        );

        __m256 fva_b = _mm256_cvtepi32_ps(
            _mm256_setr_epi32(
                ptr_b[k+0], ptr_b[k+1], ptr_b[k+2], ptr_b[k+3],
                ptr_b[k+4], ptr_b[k+5], ptr_b[k+6], ptr_b[k+7]
            )
        );

        __m256i c = _mm256_set1_epi32(127);

        // evil floating point bit hack
        __m256i logva_r = _mm256_sub_epi32(_mm256_srli_epi32((__m256i)fva_r, 23), c);
        __m256i logva_g = _mm256_sub_epi32(_mm256_srli_epi32((__m256i)fva_g, 23), c);
        __m256i logva_b = _mm256_sub_epi32(_mm256_srli_epi32((__m256i)fva_b, 23), c);

        for(size_t i = 0; i < 8; ++i){
            ptr_r[k+i] = *((uint8_t*)&logva_r + (i << 2));
            ptr_g[k+i] = *((uint8_t*)&logva_g + (i << 2));
            ptr_b[k+i] = *((uint8_t*)&logva_b + (i << 2));
        }
    }
}

#include<math.h>

inline int log2i(int x){ return log(x) / log(2); }

// simd, log, .bmp, 8 bits per channel, no pipeline
void simd_log_bmp_8bpc_npl(imgfile_t* imgfile){
    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];

        size_t j = 0;
        for(j = 0; j < (imgfile->width & ~0x1F); j += 32){
            simd_log_bmp_8bpc(ptr_r, ptr_g, ptr_b);
        }

        for(; j < imgfile->width; ++j){
            ptr_r[j] = log2i(ptr_r[j]);
            ptr_g[j] = log2i(ptr_g[j]);
            ptr_b[j] = log2i(ptr_b[j]);
        }
    }
}

// no simd, log, .bmp, 8 bits per channel, no pipeline
void log_bmp_8bpc_npl(imgfile_t* imgfile){
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            imgfile->imgdata._8bpc.r[i][j] = log2i(imgfile->imgdata._8bpc.r[i][j]);
            imgfile->imgdata._8bpc.g[i][j] = log2i(imgfile->imgdata._8bpc.g[i][j]);
            imgfile->imgdata._8bpc.b[i][j] = log2i(imgfile->imgdata._8bpc.b[i][j]);
        }
    }
}
