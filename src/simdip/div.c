#include<simdip/div.h>

/*
OP_DIV
divide every pixel in the image by constant
*/

// simd, divide by constant, 8 bits per channel, pipeline
void simd_div_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, uint8_t c){
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

    __m256i vres_r = _mm256_packus_epi16(
        _mm256_permute4x64_epi64(
            _mm256_packus_epi32(
                _mm256_cvtps_epi32(_mm256_div_ps(vr[0], _mm256_set1_ps(c))),
                _mm256_cvtps_epi32(_mm256_div_ps(vr[2], _mm256_set1_ps(c)))
            ),
            0xD8
        ),
        _mm256_permute4x64_epi64(
            _mm256_packus_epi32(
                _mm256_cvtps_epi32(_mm256_div_ps(vr[1], _mm256_set1_ps(c))),
                _mm256_cvtps_epi32(_mm256_div_ps(vr[3], _mm256_set1_ps(c)))
            ),
            0xD8
        )
    );

    __m256i vres_g = _mm256_packus_epi16(
        _mm256_permute4x64_epi64(
            _mm256_packus_epi32(
                _mm256_cvtps_epi32(_mm256_div_ps(vg[0], _mm256_set1_ps(c))),
                _mm256_cvtps_epi32(_mm256_div_ps(vg[2], _mm256_set1_ps(c)))
            ),
            0xD8
        ),
        _mm256_permute4x64_epi64(
            _mm256_packus_epi32(
                _mm256_cvtps_epi32(_mm256_div_ps(vg[1], _mm256_set1_ps(c))),
                _mm256_cvtps_epi32(_mm256_div_ps(vg[3], _mm256_set1_ps(c)))
            ),
            0xD8
        )
    );

    __m256i vres_b = _mm256_packus_epi16(
        _mm256_permute4x64_epi64(
            _mm256_packus_epi32(
                _mm256_cvtps_epi32(_mm256_div_ps(vb[0], _mm256_set1_ps(c))),
                _mm256_cvtps_epi32(_mm256_div_ps(vb[2], _mm256_set1_ps(c)))
            ),
            0xD8
        ),
        _mm256_permute4x64_epi64(
            _mm256_packus_epi32(
                _mm256_cvtps_epi32(_mm256_div_ps(vb[1], _mm256_set1_ps(c))),
                _mm256_cvtps_epi32(_mm256_div_ps(vb[3], _mm256_set1_ps(c)))
            ),
            0xD8
        )
    );

    _mm256_store_si256((__m256i*)ptr_r, vres_r);
    _mm256_store_si256((__m256i*)ptr_g, vres_g);
    _mm256_store_si256((__m256i*)ptr_b, vres_b);
}

// simd, divide by constant, 8 bits per channel, no pipeline
void simd_div_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];

        size_t j = 0;
        for(j = 0; j < (imgfile->width & ~0x1F); j += 32){
            simd_div_8bpc(ptr_r, ptr_b, ptr_g, c);
        }

        for(; j < imgfile->width; ++j){
            ptr_r[j] /= c;
            ptr_g[j] /= c;
            ptr_b[j] /= c;
        }
    }
}

// no simd, divide by constant, 8 bits per channel, no pipeline
void div_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            imgfile->imgdata._8bpc.r[i][j] /= c;
            imgfile->imgdata._8bpc.g[i][j] /= c;
            imgfile->imgdata._8bpc.b[i][j] /= c;
        }
    }
}
