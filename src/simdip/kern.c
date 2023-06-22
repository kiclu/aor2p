#include<simdip/kern.h>

/*
OP_KERN
apply kernel to image
*/

typedef uint8_t** ch_ptr_t;

static size_t ih;
static ch_ptr_t kr;
static ch_ptr_t kg;
static ch_ptr_t kb;

static inline void _swap(ch_ptr_t* r, ch_ptr_t* kr){
    ch_ptr_t tmp = *r; *r = *kr; *kr = tmp;
}

static inline void simd_kern_8bpc(uint8_t** ptr_r, uint8_t** ptr_g, uint8_t** ptr_b, kern_t k, size_t i, size_t j){
    __m256 vres_r = _mm256_set1_ps(0);
    __m256 vres_g = _mm256_set1_ps(0);
    __m256 vres_b = _mm256_set1_ps(0);

    for(size_t ki = 0; ki < k.n; ++ki){
        for(size_t kj = 0; kj < k.m; ++kj){
            vres_r = _mm256_add_ps(
                _mm256_mul_ps(
                    _mm256_cvtepi32_ps(
                        _mm256_cvtepu8_epi32(
                            _mm_lddqu_si128((__m128i*)&ptr_r[i+ki][j+kj])
                        )
                    ),
                    _mm256_set1_ps(k.kern[ki][kj])
                ),
                vres_r
            );

            vres_g = _mm256_add_ps(
                _mm256_mul_ps(
                    _mm256_cvtepi32_ps(
                        _mm256_cvtepu8_epi32(
                            _mm_lddqu_si128((__m128i*)&ptr_g[i+ki][j+kj])
                        )
                    ),
                    _mm256_set1_ps(k.kern[ki][kj])
                ),
                vres_g
            );

            vres_b = _mm256_add_ps(
                _mm256_mul_ps(
                    _mm256_cvtepi32_ps(
                        _mm256_cvtepu8_epi32(
                            _mm_lddqu_si128((__m128i*)&ptr_b[i+ki][j+kj])
                        )
                    ),
                    _mm256_set1_ps(k.kern[ki][kj])
                ),
                vres_b
            );
        }
    }

    vres_r = _mm256_min_ps(vres_r, _mm256_set1_ps(255));
    vres_g = _mm256_min_ps(vres_g, _mm256_set1_ps(255));
    vres_b = _mm256_min_ps(vres_b, _mm256_set1_ps(255));
    vres_r = _mm256_max_ps(vres_r, _mm256_set1_ps(0));
    vres_g = _mm256_max_ps(vres_g, _mm256_set1_ps(0));
    vres_b = _mm256_max_ps(vres_b, _mm256_set1_ps(0));

    __m256i ivres_r = _mm256_cvtps_epi32(vres_r);
    __m256i ivres_g = _mm256_cvtps_epi32(vres_g);
    __m256i ivres_b = _mm256_cvtps_epi32(vres_b);

    for(size_t ri = 0; ri < 8; ++ri){
        kr[i + k.n/2][j + k.m/2 + ri] = *((uint8_t*)&ivres_r + (ri << 2));
        kg[i + k.n/2][j + k.m/2 + ri] = *((uint8_t*)&ivres_g + (ri << 2));
        kb[i + k.n/2][j + k.m/2 + ri] = *((uint8_t*)&ivres_b + (ri << 2));
    }
}

// simd, apply kernel to pixel, 8 bits per channel, no pipeline
void simd_kern_8bpc_npl(imgfile_t* imgfile, kern_t k){
    for(size_t i = 0; i < imgfile->height - k.n; ++i){
        for(size_t j = 0; j < imgfile->width - k.m; j += 8){
            simd_kern_8bpc(
                imgfile->imgdata._8bpc.r,
                imgfile->imgdata._8bpc.g,
                imgfile->imgdata._8bpc.b,
                k,
                i,
                j
            );
        }
    }

    _swap(&imgfile->imgdata._8bpc.r, &kr);
    _swap(&imgfile->imgdata._8bpc.g, &kg);
    _swap(&imgfile->imgdata._8bpc.b, &kb);
}

static inline uint8_t _adds(uint8_t** p, size_t i, size_t j, kern_t k){
    float sum = 0;
    for(size_t ki = 0; ki < k.n; ++ki){
        for(size_t kj = 0; kj < k.m; ++kj){
            sum += p[i+ki][j+kj] * k.kern[ki][kj];
        }
    }
    if(sum >= 255.f) return 255;
    if(sum < 0) return 0;
    return sum;
}


// no simd, apply kernel to pixel, 8 bits per channel, no pipeline
void kern_8bpc_npl(imgfile_t* imgfile, kern_t k){
    for(size_t i = 0; i < imgfile->height - k.n; ++i){
        for(size_t j = 0; j < imgfile->width - k.m; ++j){
            kr[i + k.n/2][j + k.m/2] = _adds(imgfile->imgdata._8bpc.r, i, j, k);
            kg[i + k.n/2][j + k.m/2] = _adds(imgfile->imgdata._8bpc.g, i, j, k);
            kb[i + k.n/2][j + k.m/2] = _adds(imgfile->imgdata._8bpc.b, i, j, k);
        }
    }

    _swap(&imgfile->imgdata._8bpc.r, &kr);
    _swap(&imgfile->imgdata._8bpc.g, &kg);
    _swap(&imgfile->imgdata._8bpc.b, &kb);
}

static bool initialized = false;
void kern_init(size_t h, size_t w){
    if(initialized) return;
    initialized = true;

    ih = h;
    kr = (uint8_t**)malloc(h * sizeof(uint8_t*));
    kg = (uint8_t**)malloc(h * sizeof(uint8_t*));
    kb = (uint8_t**)malloc(h * sizeof(uint8_t*));
    for(size_t i = 0; i < h; ++i){
        kr[i] = (uint8_t*)aligned_alloc(32, (w * sizeof(uint8_t) | 0x7) + 1);
        kg[i] = (uint8_t*)aligned_alloc(32, (w * sizeof(uint8_t) | 0x7) + 1);
        kb[i] = (uint8_t*)aligned_alloc(32, (w * sizeof(uint8_t) | 0x7) + 1);
    }
}

void kern_free(){
    if(!initialized) return;
    for(size_t i = 0; i < ih; ++i){
        free(kr[i]); free(kg[i]); free(kb[i]);
    }
    free(kr); free(kg); free(kb);
}
