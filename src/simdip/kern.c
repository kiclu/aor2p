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

static inline int8_t _adds(int8_t a, int8_t b){
    if(a + b > 127) return 127;
    if(a + b < 0) return 0;
    return a + b;
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

    int8_t** r = (int8_t**)malloc(imgfile->height * sizeof(int8_t*));
    int8_t** g = (int8_t**)malloc(imgfile->height * sizeof(int8_t*));
    int8_t** b = (int8_t**)malloc(imgfile->height * sizeof(int8_t*));
    if(NULL == r || NULL == g || NULL == b) printf("!");
    for(size_t i = 0; i < imgfile->height; ++i){
        r[i] = (int8_t*)malloc(imgfile->width * sizeof(int8_t));
        g[i] = (int8_t*)malloc(imgfile->width * sizeof(int8_t));
        b[i] = (int8_t*)malloc(imgfile->width * sizeof(int8_t));
        if(NULL == r[i] || NULL == g[i] || NULL == b[i]) printf("!");
    }

    for(size_t i = n/2; i < imgfile->height - n/2; ++i){
        for(size_t j = m/2; j < imgfile->width - m/2; ++j){
            for(size_t di = 0; di < n; ++di){
                for(size_t dj = 0; dj < m; ++dj){
                    r[i][j] = _adds(r[i][j], imgfile->imgdata._8bpc.r[i+di-n/2][j+dj-m/2] * k.kern[di][dj]);
                    g[i][j] = _adds(g[i][j], imgfile->imgdata._8bpc.g[i+di-n/2][j+dj-m/2] * k.kern[di][dj]);
                    b[i][j] = _adds(b[i][j], imgfile->imgdata._8bpc.b[i+di-n/2][j+dj-m/2] * k.kern[di][dj]);
                }
            }
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
