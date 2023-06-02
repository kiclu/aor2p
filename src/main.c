#include<stdio.h>

#include<imgparse/imgparse.h>
#include<cliparse/cliparse.h>

#include<simdip/simdip.h>

int main(int argc, const char** argv){
    if(argc < 2){
        // TODO: print help page
        return 1;
    }
    
    imgfile_t* imgfile = img_fread(argv[1]);

    img_print_info(imgfile);

    // add_bmp_8bpc_npl(imgfile, 0x70);
    simd_adds_bmp_8bpc_npl(imgfile, 0xA0);

    // simd_sub_bmp_8bpc_npl(imgfile, 0x10);

    // simd_gs_bmp_8bpc_npl(imgfile);

    img_fwrite(imgfile, argv[2]);

    img_free(imgfile);

    return 0;
}
