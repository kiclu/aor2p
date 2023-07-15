#ifndef _AOR2P_IMG_IMGFILE_H_
#define _AOR2P_IMG_IMGFILE_H_

#include<stdint.h>
#include<stdlib.h>

typedef enum imgfiletype { PNG, BMP } imgfiletype_t;

typedef struct imgdata_8bpc{
    uint8_t** r;
    uint8_t** g;
    uint8_t** b;
    uint8_t** a;
} imgdata_8bpc;

typedef struct imgdata_16bpc{
    uint16_t** r;
    uint16_t** g;
    uint16_t** b;
} imgdata_16bpc;

typedef union imgdata{
    imgdata_8bpc  _8bpc;
    imgdata_16bpc _16bpc;
} imgdata_t;

typedef struct imgfile{
    char*         filename;

    size_t        width;
    size_t        height;
    size_t        bit_depth;
    size_t        channels;

    imgdata_t     imgdata;
    imgfiletype_t filetype;
} imgfile_t;

#endif//_AOR2P_IMG_IMGFILE_H_
