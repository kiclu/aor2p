#include<simdip/gs.h>

// simd, convert to grayscale, .bmp, 8 bits per channel, pipeline
void simd_gs_bmp_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b){
    for(uint32_t k = 0; k < 32; k += 8){
        __m256 vr = _mm256_cvtepi32_ps(
            _mm256_setr_epi32(
                ptr_r[k+0], ptr_r[k+1], ptr_r[k+2], ptr_r[k+3],
                ptr_r[k+4], ptr_r[k+5], ptr_r[k+6], ptr_r[k+7]
            )
        );

        __m256 sum = _mm256_mul_ps(vr, _mm256_set1_ps(0.299));

        __m256 vg = _mm256_cvtepi32_ps(
            _mm256_setr_epi32(
                ptr_g[k+0], ptr_g[k+1], ptr_g[k+2], ptr_g[k+3],
                ptr_g[k+4], ptr_g[k+5], ptr_g[k+6], ptr_g[k+7]
            )
        );

        sum = _mm256_fmadd_ps(vg, _mm256_set1_ps(0.587), sum);

        __m256 vb = _mm256_cvtepi32_ps(
            _mm256_setr_epi32(
                ptr_b[k+0], ptr_b[k+1], ptr_b[k+2], ptr_b[k+3],
                ptr_b[k+4], ptr_b[k+5], ptr_b[k+6], ptr_b[k+7]
            )
        );

        sum = _mm256_fmadd_ps(vb, _mm256_set1_ps(0.114), sum);

        __m256i gs = _mm256_cvtps_epi32(sum);

        for(size_t i = 0; i < 8; ++i){
            ptr_r[k+i] = *((uint8_t*)&gs + (i << 2));
            ptr_g[k+i] = *((uint8_t*)&gs + (i << 2));
            ptr_b[k+i] = *((uint8_t*)&gs + (i << 2));
        }
    }
}

static inline uint8_t _gs(uint8_t r, uint8_t g, uint8_t b){
    return r * 0.299f + g * 0.587f + b * 0.114f;
}

// simd, convert to grayscale, .bmp, 8 bits per channel, no pipeline
void simd_gs_bmp_8bpc_npl(imgfile_t* imgfile){
    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];

        size_t j = 0;
        for(; j < (imgfile->width & ~0x1F); j += 32){
            simd_gs_bmp_8bpc(ptr_r + j, ptr_g + j, ptr_b + j);
        }

        for(; j < imgfile->width; ++j){
            ptr_r[j] = ptr_g[j] = ptr_b[j] = _gs(ptr_r[j], ptr_g[j], ptr_b[j]);
        }
    }
}

// no simd, convert to grayscale, .bmp, 8 bits per channel, no pipeline
void gs_bmp_8bpc_npl(imgfile_t* imgfile){
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
