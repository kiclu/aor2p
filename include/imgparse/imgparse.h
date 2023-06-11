#ifndef _AOR2P_IMGPARSE_H
#define _AOR2P_IMGPARSE_H

#include<imgparse/imgfile.h>

void img_print_info(imgfile_t* imgfile);

imgfile_t* img_fread_bmp(const char* filename);
imgfile_t* img_fread(const char* filename);

int img_fwrite_png(imgfile_t* imgfile, const char* filename);
int img_fwrite_bmp(imgfile_t* imgfile, const char* filename);
int img_fwrite(imgfile_t* imgfile, const char* filename);

void img_free(imgfile_t* imgfile);

#endif//_AOR2P_IMGPARSE_H
