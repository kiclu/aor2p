#include<simdip/log.h>

/*
OP_LOG
replace every pixel of image with its logarithm
*/

// https://en.wikipedia.org/wiki/Fast_inverse_square_root

#define fva_r(x) _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm_loadu_si64(ptr_r+8*(x))))
#define fva_g(x) _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm_loadu_si64(ptr_g+8*(x))))
#define fva_b(x) _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm_loadu_si64(ptr_b+8*(x))))

// simd, log, 8 bits per channel, pipeline
void simd_log_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b){
    __m256i c = _mm256_set1_epi32(127);

    // evil floating point bit hack
    __m256i logva_r[] = {
        _mm256_sub_epi32(_mm256_srli_epi32((__m256i)fva_r(0), 23), c),
        _mm256_sub_epi32(_mm256_srli_epi32((__m256i)fva_r(1), 23), c),
        _mm256_sub_epi32(_mm256_srli_epi32((__m256i)fva_r(2), 23), c),
        _mm256_sub_epi32(_mm256_srli_epi32((__m256i)fva_r(3), 23), c)
    };

    __m256i logva_g[] = {
        _mm256_sub_epi32(_mm256_srli_epi32((__m256i)fva_g(0), 23), c),
        _mm256_sub_epi32(_mm256_srli_epi32((__m256i)fva_g(1), 23), c),
        _mm256_sub_epi32(_mm256_srli_epi32((__m256i)fva_g(2), 23), c),
        _mm256_sub_epi32(_mm256_srli_epi32((__m256i)fva_g(3), 23), c)
    };

    __m256i logva_b[] = {
        _mm256_sub_epi32(_mm256_srli_epi32((__m256i)fva_b(0), 23), c),
        _mm256_sub_epi32(_mm256_srli_epi32((__m256i)fva_b(1), 23), c),
        _mm256_sub_epi32(_mm256_srli_epi32((__m256i)fva_b(2), 23), c),
        _mm256_sub_epi32(_mm256_srli_epi32((__m256i)fva_b(3), 23), c)
    };

    __m256i vres_r = _mm256_packus_epi16(
        _mm256_permute4x64_epi64(_mm256_packus_epi32(logva_r[0], logva_r[2]), 0xD8),
        _mm256_permute4x64_epi64(_mm256_packus_epi32(logva_r[1], logva_r[3]), 0xD8)
    );

    __m256i vres_g = _mm256_packus_epi16(
        _mm256_permute4x64_epi64(_mm256_packus_epi32(logva_g[0], logva_g[2]), 0xD8),
        _mm256_permute4x64_epi64(_mm256_packus_epi32(logva_g[1], logva_g[3]), 0xD8)
    );

    __m256i vres_b = _mm256_packus_epi16(
        _mm256_permute4x64_epi64(_mm256_packus_epi32(logva_b[0], logva_b[2]), 0xD8),
        _mm256_permute4x64_epi64(_mm256_packus_epi32(logva_b[1], logva_b[3]), 0xD8)
    );

    _mm256_store_si256((__m256i*)ptr_r, vres_r);
    _mm256_store_si256((__m256i*)ptr_g, vres_g);
    _mm256_store_si256((__m256i*)ptr_b, vres_b);
}

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
            simd_log_8bpc(ptr_r, ptr_g, ptr_b);
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
