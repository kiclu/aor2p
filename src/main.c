#include<stdio.h>

#include<img/imgparse.h>
#include<cli/parse.h>
#include<ip.h>

int main(int argc, const char** argv){
    args_t* args = cliparse(argc, argv);
    if(NULL == args) return -1;

#ifdef SIMDIP_VERBOSE
    img_print_info(args->imgfile);
#endif//SIMDIP_VERBOSE

    uint64_t time = process(args);
    printf("time taken: %luns\n", time);
    
    cliparse_free(args);

    return 0;
}
