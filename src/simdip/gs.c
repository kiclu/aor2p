#include<simdip/gs.h>

// simd, convert to grayscale, .bmp, 8 bits per channel, pipeline
void simd_gs_bmp_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b){
    __m256 vr = _mm256_cvtepi32_ps(
        _mm256_setr_epi32(
            ptr_r[0], ptr_r[1], ptr_r[2], ptr_r[3],
            ptr_r[4], ptr_r[5], ptr_r[6], ptr_r[7]
        )
    );

    __m256 sum = _mm256_mul_ps(vr, _mm256_set1_ps(0.299));

    __m256 vg = _mm256_cvtepi32_ps(
        _mm256_setr_epi32(
            ptr_g[0], ptr_g[1], ptr_g[2], ptr_g[3],
            ptr_g[4], ptr_g[5], ptr_g[6], ptr_g[7]
        )
    );

    sum = _mm256_fmadd_ps(vg, _mm256_set1_ps(0.587), sum);

    __m256 vb = _mm256_cvtepi32_ps(
        _mm256_setr_epi32(
            ptr_b[0], ptr_b[1], ptr_b[2], ptr_b[3],
            ptr_b[4], ptr_b[5], ptr_b[6], ptr_b[7]
        )
    );

    sum = _mm256_fmadd_ps(vb, _mm256_set1_ps(0.114), sum);

    __m256i gs = _mm256_cvtps_epi32(sum);
    uint8_t* gs_8b = (uint8_t*)&gs;

    for(size_t i = 0; i < 8; ++i){
        ptr_r[i] = *((uint8_t*)&gs + (i << 2));
        ptr_g[i] = *((uint8_t*)&gs + (i << 2));
        ptr_b[i] = *((uint8_t*)&gs + (i << 2));
    }
}

// simd, convert to grayscale, .bmp, 8 bits per channel, no pipeline
void simd_gs_bmp_8bpc_npl(imgfile_t* imgfile){
    printf("simd_gs_bmp_8bpc_npp\n");

    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];
        size_t j = 0;
        for(; j < (imgfile->width & ~0x1F); j += 8, ptr_r += 8, ptr_g += 8, ptr_b += 8){
            simd_gs_bmp_8bpc(ptr_r, ptr_g, ptr_b);
        }
        for(; j < imgfile->width; ++j){
            // TODO: implement
        }
    }
}

// no simd, convert to grayscale, .bmp, 8 bits per channel, no pipeline
void gs_bmp_8bpc_npl(imgfile_t*);