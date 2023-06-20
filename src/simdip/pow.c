#include<simdip/pow.h>

/*
OP_POW
raise every pixel of image to power of constant
*/

// simd, pow, .bmp, 8 bits per channel, pipeline
void simd_pow_bmp_8bpc(uint8_t* ptr_r, uint8_t* ptr_g, uint8_t* ptr_b, uint8_t c){
    for(size_t k = 0; k < 32; k += 16){
        __m256i va_r = _mm256_setr_epi16(
            ptr_r[k+0],  ptr_r[k+1],  ptr_r[k+2],  ptr_r[k+3],
            ptr_r[k+4],  ptr_r[k+5],  ptr_r[k+6],  ptr_r[k+7],
            ptr_r[k+8],  ptr_r[k+9],  ptr_r[k+10], ptr_r[k+11],
            ptr_r[k+12], ptr_r[k+13], ptr_r[k+14], ptr_r[k+15]
        );
        __m256i vres_r = _mm256_set1_epi16(1);
        __m256i vpow_r = va_r;
        for(uint8_t pc = c; pc; pc >>= 1){
            if(pc & 0b1){
                vres_r = _mm256_mullo_epi16(vres_r, vpow_r);
            }
            vpow_r = _mm256_mullo_epi16(vpow_r, vpow_r);
        }

        __m256i va_g = _mm256_setr_epi16(
            ptr_g[k+0],  ptr_g[k+1],  ptr_g[k+2],  ptr_g[k+3],
            ptr_g[k+4],  ptr_g[k+5],  ptr_g[k+6],  ptr_g[k+7],
            ptr_g[k+8],  ptr_g[k+9],  ptr_g[k+10], ptr_g[k+11],
            ptr_g[k+12], ptr_g[k+13], ptr_g[k+14], ptr_g[k+15]
        );
        __m256i vres_g = _mm256_set1_epi16(1);
        __m256i vpow_g = va_g;
        for(uint8_t pc = c; pc; pc >>= 1){
            if(pc & 0b1){
                vres_g = _mm256_mullo_epi16(vres_g, vpow_g);
            }
            vpow_g = _mm256_mullo_epi16(vpow_g, vpow_g);
        }

        __m256i va_b = _mm256_setr_epi16(
            ptr_b[k+0],  ptr_b[k+1],  ptr_b[k+2],  ptr_b[k+3],
            ptr_b[k+4],  ptr_b[k+5],  ptr_b[k+6],  ptr_b[k+7],
            ptr_b[k+8],  ptr_b[k+9],  ptr_b[k+10], ptr_b[k+11],
            ptr_b[k+12], ptr_b[k+13], ptr_b[k+14], ptr_b[k+15]
        );
        __m256i vres_b = _mm256_set1_epi16(1);
        __m256i vpow_b = va_b;
        for(uint8_t pc = c; pc; pc >>= 1){
            if(pc & 0b1){
                vres_b = _mm256_mullo_epi16(vres_b, vpow_b);
            }
            vpow_b = _mm256_mullo_epi16(vpow_b, vpow_b);
        }

        for(size_t i = 0; i < 16; ++i){
            ptr_r[k+i] = *((uint8_t*)&vres_r + (i << 1));
            ptr_g[k+i] = *((uint8_t*)&vres_g + (i << 1));
            ptr_b[k+i] = *((uint8_t*)&vres_b + (i << 1));
        }
    }
}

#include<math.h>

// simd, pow, .bmp, 8 bits per channel, no pipeline
void simd_pow_bmp_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        uint8_t* ptr_r = imgfile->imgdata._8bpc.r[i];
        uint8_t* ptr_g = imgfile->imgdata._8bpc.g[i];
        uint8_t* ptr_b = imgfile->imgdata._8bpc.b[i];

        size_t j = 0;
        for(j = 0; j < (imgfile->width & ~0x1F); j += 32){
            simd_pow_bmp_8bpc(ptr_r, ptr_b, ptr_g, c);
        }

        for(; j < imgfile->width; ++j){
            *ptr_r++ *= pow(*ptr_r, c);
            *ptr_g++ *= pow(*ptr_g, c);
            *ptr_b++ *= pow(*ptr_b, c);
        }
    }
}

// no simd, pow, .bmp, 8 bits per channel, no pipeline
void pow_bmp_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            imgfile->imgdata._8bpc.r[i][j] = pow(imgfile->imgdata._8bpc.r[i][j], c);
            imgfile->imgdata._8bpc.g[i][j] = pow(imgfile->imgdata._8bpc.g[i][j], c);
            imgfile->imgdata._8bpc.b[i][j] = pow(imgfile->imgdata._8bpc.b[i][j], c);
        }
    }
}
