#ifndef _AOR2P_IMG_IMGPARSE_H_
#define _AOR2P_IMG_IMGPARSE_H_

#include<img/imgfile.h>

void        img_print_info(imgfile_t* imgfile);
imgfile_t*  img_fread(const char* filename);
int         img_fwrite(imgfile_t* imgfile, const char* filename);
void        img_free(imgfile_t* imgfile);

#endif//_AOR2P_IMG_IMGPARSE_H_
