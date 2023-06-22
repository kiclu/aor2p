#include<imgparse/imgparse.h>

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include<stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include<stb/stb_image_write.h>

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

static imgfile_t* img_fread_png(const char* filename){
    imgfile_t* imgfile = (imgfile_t*)malloc(sizeof(imgfile_t));
    imgfile->filetype = PNG;
    imgfile->filename = (char*)malloc(strlen(filename) + 1);
    strcpy(imgfile->filename, filename);

    int h, w, c;
    if(NULL == (imgfile->img = stbi_load(filename, &h, &w, &c, 4))){
        // TODO: handle image load failed
        // free(imgfile-filename);
        return NULL;
    }
    
    imgfile->height = h;
    imgfile->width = w;
    imgfile->channels = c;
    imgfile->bit_depth = 32;

    imgfile->imgdata._8bpc.r = (uint8_t**)malloc(imgfile->height * sizeof(uint8_t*));
    imgfile->imgdata._8bpc.g = (uint8_t**)malloc(imgfile->height * sizeof(uint8_t*));
    imgfile->imgdata._8bpc.b = (uint8_t**)malloc(imgfile->height * sizeof(uint8_t*));

    imgfile->imgdata._8bpc.a = (uint8_t**)malloc(imgfile->height * sizeof(uint8_t*));

    for(size_t i = 0; i < imgfile->height; ++i){
        imgfile->imgdata._8bpc.r[i] = (uint8_t*)aligned_alloc(32, imgfile->width);
        imgfile->imgdata._8bpc.g[i] = (uint8_t*)aligned_alloc(32, imgfile->width);
        imgfile->imgdata._8bpc.b[i] = (uint8_t*)aligned_alloc(32, imgfile->width);
        
        imgfile->imgdata._8bpc.a[i] = (uint8_t*)malloc(imgfile->width * sizeof(uint8_t));
    }

    size_t k = 0;
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            imgfile->imgdata._8bpc.r[i][j] = imgfile->img[k++];
            imgfile->imgdata._8bpc.g[i][j] = imgfile->img[k++];
            imgfile->imgdata._8bpc.b[i][j] = imgfile->img[k++];
            imgfile->imgdata._8bpc.a[i][j] = imgfile->img[k++];
        }
    }

    return imgfile;
}

static imgfile_t* img_fread_bmp(const char* filename){
    imgfile_t* imgfile = (imgfile_t*)malloc(sizeof(imgfile_t));
    imgfile->filetype = BMP;
    imgfile->filename = (char*)malloc(strlen(filename) + 1);
    strcpy(imgfile->filename, filename);

    int h, w, c;
    if(NULL == (imgfile->img = stbi_load(filename, &h, &w, &c, 4))){
        // TODO: handle image load failed
        // free(imgfile-filename);
        return NULL;
    }
    
    imgfile->height = h;
    imgfile->width = w;
    imgfile->channels = c;
    imgfile->bit_depth = 32;

    imgfile->imgdata._8bpc.r = (uint8_t**)malloc(imgfile->height * sizeof(uint8_t*));
    imgfile->imgdata._8bpc.g = (uint8_t**)malloc(imgfile->height * sizeof(uint8_t*));
    imgfile->imgdata._8bpc.b = (uint8_t**)malloc(imgfile->height * sizeof(uint8_t*));

    imgfile->imgdata._8bpc.a = (uint8_t**)malloc(imgfile->height * sizeof(uint8_t*));

    for(size_t i = 0; i < imgfile->height; ++i){
        imgfile->imgdata._8bpc.r[i] = (uint8_t*)aligned_alloc(32, imgfile->width);
        imgfile->imgdata._8bpc.g[i] = (uint8_t*)aligned_alloc(32, imgfile->width);
        imgfile->imgdata._8bpc.b[i] = (uint8_t*)aligned_alloc(32, imgfile->width);
        
        imgfile->imgdata._8bpc.a[i] = (uint8_t*)malloc(imgfile->width * sizeof(uint8_t));
    }

    size_t k = 0;
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            imgfile->imgdata._8bpc.r[i][j] = imgfile->img[k++];
            imgfile->imgdata._8bpc.g[i][j] = imgfile->img[k++];
            imgfile->imgdata._8bpc.b[i][j] = imgfile->img[k++];
            imgfile->imgdata._8bpc.a[i][j] = imgfile->img[k++];
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

static uint8_t* make_buffer(imgfile_t* imgfile){
    uint8_t* buffer = (uint8_t*)malloc(4 * imgfile->width * imgfile->height * sizeof(uint8_t));
    size_t k = 0;
    for(size_t i = 0; i < imgfile->height; ++i){
        for(size_t j = 0; j < imgfile->width; ++j){
            buffer[k++] = imgfile->imgdata._8bpc.r[i][j];
            buffer[k++] = imgfile->imgdata._8bpc.g[i][j];
            buffer[k++] = imgfile->imgdata._8bpc.b[i][j];
            buffer[k++] = imgfile->imgdata._8bpc.a[i][j];
        }
    }
    return buffer;
}

static int img_fwrite_png(imgfile_t* imgfile, const char* filename){
    uint8_t* buffer = make_buffer(imgfile);
    stbi_write_png(filename, imgfile->height, imgfile->width, 4, buffer, 0);
    free(buffer);
    return 0;
}

static int img_fwrite_bmp(imgfile_t* imgfile, const char* filename){
    uint8_t* buffer = make_buffer(imgfile);
    stbi_write_bmp(filename, imgfile->height, imgfile->width, 4, buffer);
    free(buffer);
    return 0;
}

int img_fwrite(imgfile_t* imgfile, const char* filename){
    const char* dot = strrchr(filename, '.');
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
    // if(imgfile->filetype == BMP) bmp_img_free(&imgfile->img.bmp);

    for(uint32_t i = 0; i < imgfile->height; ++i){
        free(imgfile->imgdata._8bpc.r[i]);
        free(imgfile->imgdata._8bpc.g[i]);
        free(imgfile->imgdata._8bpc.b[i]);
    }
    
    free(imgfile->imgdata._8bpc.r);
    free(imgfile->imgdata._8bpc.g);
    free(imgfile->imgdata._8bpc.b);

    free(imgfile->filename);

    free(imgfile);
}
