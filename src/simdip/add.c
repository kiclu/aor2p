#include<op/add.h>

/*
OP_ADD
add a constant to every pixel in the image
*/

// no simd, add constant, 8 bits per channel, no pipeline
void add_8bpc_npl(imgfile_t* imgfile, uint8_t c){
    for(uint32_t i = 0; i < imgfile->height; ++i){
        for(uint32_t j = 0; j < imgfile->width; ++j){
            imgfile->imgdata._8bpc.r[i][j] += c;
            imgfile->imgdata._8bpc.g[i][j] += c;
            imgfile->imgdata._8bpc.b[i][j] += c;
        }
    }
}
