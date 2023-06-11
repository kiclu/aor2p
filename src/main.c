#include<stdio.h>

#include<imgparse/imgparse.h>
#include<cliparse/cliparse.h>
#include<simdip/simdip.h>

int main(int argc, const char** argv){
    args_t* args = cliparse(argc, argv);
    if(NULL == args){
        // TODO: handle error
        return -1;
    }

    uint64_t time = process(args);
    printf("time taken: %luns\n", time);

    img_free(args->imgfile);
    free(args);

    return 0;
}
