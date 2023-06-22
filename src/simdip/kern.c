#include<simdip/kern.h>

/*
OP_KERN
apply kernel to image
*/

// simd, apply kernel to pixel, .bmp, 8 bits per channel, pipeline
void simd_kern_bmp_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, kern_t k){

}

// simd, apply kernel to pixel, .bmp, 8 bits per channel, no pipeline
void simd_kern_bmp_8bpc_npl(imgfile_t* imgfile, kern_t k){
    for(size_t i = 0; i < imgfile->height - k.n; ++i){
        for(size_t j = 0; j < imgfile->width - k.m; ++j){
            
        }
    }
}

static inline uint8_t _adds(uint8_t** p, size_t i, size_t j, kern_t k){
    float sum = 0;
    for(size_t di = 0; di < 3; ++di){
        for(size_t dj = 0; dj < 3; ++dj){
            sum += p[i + di][j + dj] * k.kern[di][dj];
        }
    }
    if(sum >= 255.f) return 255;
    if(sum < 0) return 0;
    return (uint8_t)sum;
}

#include<stdio.h>

// no simd, apply kernel to pixel, .bmp, 8 bits per channel, no pipeline
void kern_bmp_8bpc_npl(imgfile_t* imgfile, kern_t k){
    size_t n = k.n;
    size_t m = k.m;
    printf("kern %lu x %lu:\n", n, m);
    for(size_t i = 0; i < n; ++i){
        for(size_t j = 0; j < m; ++j){
            printf("%2d ", k.kern[i][j]);
        }
        printf("\n");
    }

    uint8_t** r = (uint8_t**)malloc(imgfile->height * sizeof(int8_t*));
    uint8_t** g = (uint8_t**)malloc(imgfile->height * sizeof(int8_t*));
    uint8_t** b = (uint8_t**)malloc(imgfile->height * sizeof(int8_t*));
    if(NULL == r || NULL == g || NULL == b) printf("!");
    for(size_t i = 0; i < imgfile->height; ++i){
        r[i] = (uint8_t*)malloc(imgfile->width * sizeof(int8_t));
        g[i] = (uint8_t*)malloc(imgfile->width * sizeof(int8_t));
        b[i] = (uint8_t*)malloc(imgfile->width * sizeof(int8_t));
    }

    for(size_t i = 0; i < imgfile->height - n; ++i){
        for(size_t j = 0; j < imgfile->width - m; ++j){
            r[i][j] = _adds(imgfile->imgdata._8bpc.r, i, j, k);
            g[i][j] = _adds(imgfile->imgdata._8bpc.g, i, j, k);
            b[i][j] = _adds(imgfile->imgdata._8bpc.b, i, j, k);
        }
    }

    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            imgfile->imgdata._8bpc.r[i][j] = r[i][j];
            imgfile->imgdata._8bpc.g[i][j] = g[i][j];
            imgfile->imgdata._8bpc.b[i][j] = b[i][j];
        }

        free(r[i]); free(g[i]); free(b[i]);
    }

    free(r); free(g); free(b);
}
