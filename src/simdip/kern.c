#include<simdip/kern.h>

/*
OP_KERN
apply kernel to image
*/

static size_t ih;
static uint8_t** kr;
static uint8_t** kg;
static uint8_t** kb;

// simd, apply kernel to pixel, 8 bits per channel, pipeline
void simd_kern_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, kern_t k, size_t i, size_t j){
    for(size_t ki = 0; ki < k.n; ++ki){
        for(size_t kj = 0; kj < k.m; ++kj){
            _mm256_set1_ps(k.kern[ki][kj]);

        }
    }
}

// simd, apply kernel to pixel, 8 bits per channel, no pipeline
void simd_kern_8bpc_npl(imgfile_t* imgfile, kern_t k){

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

typedef uint8_t** ch_ptr_t;
static inline void swap_pointers(ch_ptr_t* r, ch_ptr_t* kr){
    ch_ptr_t tmp = *r; *r = *kr; *kr = tmp;
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

    swap_pointers(&imgfile->imgdata._8bpc.r, &kr);
    swap_pointers(&imgfile->imgdata._8bpc.g, &kg);
    swap_pointers(&imgfile->imgdata._8bpc.b, &kb);
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
        kr[i] = (uint8_t*)aligned_alloc(32, w * sizeof(uint8_t));
        kg[i] = (uint8_t*)aligned_alloc(32, w * sizeof(uint8_t));
        kb[i] = (uint8_t*)aligned_alloc(32, w * sizeof(uint8_t));
    }
}

void kern_free(){
    if(!initialized) return;
    for(size_t i = 0; i < ih; ++i){
        free(kr[i]); free(kg[i]); free(kb[i]);
    }
    free(kr); free(kg); free(kb);
}
