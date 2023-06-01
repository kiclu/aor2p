#ifndef _AOR2P_IMGPARSE_H
#define _AOR2P_IMGPARSE_H

#include<imgparse/imgfile.h>

#include<stdio.h>
#include<string.h>
#include<unistd.h> // access()
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>

void img_print_info(imgfile_t* imgfile){
    printf("==================================================\n");
    printf("IMAGE INFO:\n");
    printf("--------------------------------------------------\n");
    printf("path:        %s\n",    imgfile->filename);
    printf("width:       %lupx\n", imgfile->width);
    printf("height:      %lupx\n", imgfile->height);
    printf("bit depth:   %lu\n",   imgfile->bit_depth);
    printf("==================================================\n");
}

// TODO: implement
imgfile_t* img_fread_png(const char* filename){
    return NULL;
}

imgfile_t* img_fread_bmp(const char* filename){
    imgfile_t* imgfile = (imgfile_t*)malloc(sizeof(imgfile_t));
    imgfile->filetype = BMP;
    imgfile->filename = (char*)malloc(strlen(filename) + 1);
    strcpy(imgfile->filename, filename);
    bmp_img_read(&imgfile->img.bmp, filename);
    imgfile->width = imgfile->img.bmp.img_header.biWidth;
    imgfile->height = imgfile->img.bmp.img_header.biHeight - 1;
    imgfile->bit_depth = imgfile->img.bmp.img_header.biBitCount;
    if(imgfile->bit_depth == 24){
        imgfile->imgdata._8bpc.r = (uint8_t**)malloc(imgfile->height * sizeof(uint8_t*));
        imgfile->imgdata._8bpc.g = (uint8_t**)malloc(imgfile->height * sizeof(uint8_t*));
        imgfile->imgdata._8bpc.b = (uint8_t**)malloc(imgfile->height * sizeof(uint8_t*));

        for(size_t i = 0; i < imgfile->height; ++i){
            imgfile->imgdata._8bpc.r[i] = (uint8_t*)aligned_alloc(32, imgfile->width);
            imgfile->imgdata._8bpc.g[i] = (uint8_t*)aligned_alloc(32, imgfile->width);
            imgfile->imgdata._8bpc.b[i] = (uint8_t*)aligned_alloc(32, imgfile->width);
            for(size_t j = 0; j < imgfile->width; ++j){
                imgfile->imgdata._8bpc.b[i][j] = imgfile->img.bmp.img_pixels[i][j].blue;
                imgfile->imgdata._8bpc.g[i][j] = imgfile->img.bmp.img_pixels[i][j].green;
                imgfile->imgdata._8bpc.r[i][j] = imgfile->img.bmp.img_pixels[i][j].red;
            }
        }
    }
    return imgfile;
}

imgfile_t* img_fread(const char* filename){
    const char* dot = strrchr(filename, '.');
    if(NULL == dot){
        fprintf(stderr, "aor2p: error: invalid input file extension\n");
        return NULL;
    }

    bool is_png = !strcmp(dot, ".png");
    bool is_bmp = !strcmp(dot, ".bmp");

    if(!is_png && !is_bmp){
        fprintf(stderr, "aor2p: error: invalid input file extension\n");
        return NULL;
    }

    if(access(filename, F_OK)){
        fprintf(stderr, "aor2p: error: can not acces input file %s\n", filename);
        return NULL;
    }

    if(is_png) return img_fread_png(filename);
    if(is_bmp) return img_fread_bmp(filename);

    return NULL;
}

// TODO: implement
int img_fwrite_png(imgfile_t* imgfile, const char* filename){
    return -1;
}

int img_fwrite_bmp(imgfile_t* imgfile, const char* filename){
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            imgfile->img.bmp.img_pixels[i][j].blue = imgfile->imgdata._8bpc.b[i][j];
            imgfile->img.bmp.img_pixels[i][j].green = imgfile->imgdata._8bpc.g[i][j];
            imgfile->img.bmp.img_pixels[i][j].red = imgfile->imgdata._8bpc.r[i][j];
        }
    }
    return bmp_img_write(&imgfile->img.bmp, filename);
}

int img_fwrite(imgfile_t* imgfile, const char* filename){
    char* dot = strrchr(filename, '.');
    if(NULL == dot){
        fprintf(stderr, "aor2p: error: invalid output file extension\n");
        return -1;
    }

    bool is_png = !strcmp(dot, ".png");
    bool is_bmp = !strcmp(dot, ".bmp");

    if(!is_png && !is_bmp){
        fprintf(stderr, "aor2p: error: invalid output file extension\n");
        return -1;
    }

    if((is_png && imgfile->filetype != PNG) || (is_bmp && imgfile->filetype != BMP)){
        fprintf(stderr, "aor2p: error: input and output filetypes do not match\n");
        return -1;
    }

    if(is_png) return img_fwrite_png(imgfile, filename);
    if(is_bmp) return img_fwrite_bmp(imgfile, filename);

    return -1;
}

void img_free(imgfile_t* imgfile){
    if(imgfile->filetype == BMP) bmp_img_free(&imgfile->img.bmp);
}

#endif//_AOR2P_IMGPARSE_H
