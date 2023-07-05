#include<simdip/gs.h>

/*
// simd, convert to grayscale, 8 bits per channel, pipeline
void simd_gs_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b){
    __m256 vr[] = {
        _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm_loadu_si64(ptr_r))),
        _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm_loadu_si64(ptr_r+8))),
        _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm_loadu_si64(ptr_r+16))),
        _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm_loadu_si64(ptr_r+24)))
    };

    __m256 vg[] = {
        _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm_loadu_si64(ptr_g))),
        _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm_loadu_si64(ptr_g+8))),
        _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm_loadu_si64(ptr_g+16))),
        _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm_loadu_si64(ptr_g+24)))
    };

    __m256 vb[] = {
        _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm_loadu_si64(ptr_b))),
        _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm_loadu_si64(ptr_b+8))),
        _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm_loadu_si64(ptr_b+16))),
        _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm_loadu_si64(ptr_b+24)))
    };

    __m256 sum[] = {
        _mm256_fmadd_ps(
            vb[0], _mm256_set1_ps(0.114),
            _mm256_fmadd_ps(
                vg[0], _mm256_set1_ps(0.587),
                _mm256_mul_ps(vr[0], _mm256_set1_ps(0.299))
            )
        ),
        _mm256_fmadd_ps(
            vb[1], _mm256_set1_ps(0.114),
            _mm256_fmadd_ps(
                vg[1], _mm256_set1_ps(0.587),
                _mm256_mul_ps(vr[1], _mm256_set1_ps(0.299))
            )
        ),
        _mm256_fmadd_ps(
            vb[2], _mm256_set1_ps(0.114),
            _mm256_fmadd_ps(
                vg[2], _mm256_set1_ps(0.587),
                _mm256_mul_ps(vr[2], _mm256_set1_ps(0.299))
            )
        ),
        _mm256_fmadd_ps(
            vb[3], _mm256_set1_ps(0.114),
            _mm256_fmadd_ps(
                vg[3], _mm256_set1_ps(0.587),
                _mm256_mul_ps(vr[3], _mm256_set1_ps(0.299))
            )
        ),
    };

    __m256i vgs[] = {
        _mm256_cvtps_epi32(sum[0]),
        _mm256_cvtps_epi32(sum[1]),
        _mm256_cvtps_epi32(sum[2]),
        _mm256_cvtps_epi32(sum[3])
    };

    __m256i vres = _mm256_packus_epi16(
        _mm256_permute4x64_epi64(_mm256_packus_epi32(vgs[0], vgs[2]), 0xD8),
        _mm256_permute4x64_epi64(_mm256_packus_epi32(vgs[1], vgs[3]), 0xD8)
    );

    _mm256_store_si256((__m256i*)ptr_r, vres);
    _mm256_store_si256((__m256i*)ptr_g, vres);
    _mm256_store_si256((__m256i*)ptr_b, vres);
}
*/
static inline uint8_t _gs(uint8_t r, uint8_t g, uint8_t b){
    return r * 0.299f + g * 0.587f + b * 0.114f;
}

// simd, convert to grayscale, 8 bits per channel, no pipeline
void simd_gs_8bpc_npl(imgfile_t* imgfile){
    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];

        size_t j = 0;
        for(; j < (imgfile->width & ~0x1F); j += 32){
            // simd_gs_8bpc(ptr_r + j, ptr_g + j, ptr_b + j);
        }

        for(; j < imgfile->width; ++j){
            ptr_r[j] = ptr_g[j] = ptr_b[j] = _gs(ptr_r[j], ptr_g[j], ptr_b[j]);
        }
    }
}

// no simd, convert to grayscale, 8 bits per channel, no pipeline
void gs_8bpc_npl(imgfile_t* imgfile){
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            uint8_t gs = _gs(
                imgfile->imgdata._8bpc.r[i][j],
                imgfile->imgdata._8bpc.g[i][j],
                imgfile->imgdata._8bpc.b[i][j]
            );
            imgfile->imgdata._8bpc.r[i][j] = gs;
            imgfile->imgdata._8bpc.g[i][j] = gs;
            imgfile->imgdata._8bpc.b[i][j] = gs;
        }
    }
}
