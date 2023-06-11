#include<simdip/simdip.h>

#include<cliparse/cliparse.h>
#include<imgparse/imgparse.h>
#include<time.h>

static struct timespec timer_start(){
    struct timespec start_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
    return start_time;
}

// call this function to end a timer, returning nanoseconds elapsed as a long
uint64_t timer_end(struct timespec start_time){
    struct timespec end_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
    return (end_time.tv_sec - start_time.tv_sec) * 1000000000UL + (end_time.tv_nsec - start_time.tv_nsec);;
}

// process, no simd & no pipeline
static void process_ns_np(args_t* args){
    for(pnode_t* i = args->signal_chain; i; i = i->next){
        switch(i->op){
            case OP_ADD:    add_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_SUB:    sub_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_ISUB:   subi_bmp_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            // case OP_MUL:    mul_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            // case OP_DIV:    div_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            // case OP_IDIV:   divi_bmp_8bpc_npl  (args->imgfile, i->arg.op_const); break;

            // case OP_ADDS:   adds_bmp_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            // case OP_SUBS:   subs_bmp_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            // case OP_ISUBS:  subis_bmp_8bpc_npl (args->imgfile, i->arg.op_const); break;

            // case OP_POW:    pow_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            // case OP_LOG:    log_bmp_8bpc_npl   (args->imgfile);                  break;
            // case OP_ABS:    abs_bmp_8bpc_npl   (args->imgfile);                  break;
            // case OP_MIN:    min_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            // case OP_MAX:    max_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;

            // case OP_NEG:    neg_bmp_8bpc_npl   (args->imgfile);                  break;
            case OP_GS:     gs_bmp_8bpc_npl    (args->imgfile);                  break;

            // case OP_KERN:   kern_bmp_8bpc_npl  (args->imgfile, i->arg.op_kern);  break;

            case OP_WR: img_fwrite(args->imgfile, i->arg.op_fileio); break;
        }
    }
}

// process, no simd & pipeline
static void process_ns(args_t* args){

}

// process, simd & no pipeline
static void process_np(args_t* args){
    for(pnode_t* i = args->signal_chain; i; i = i->next){
        switch(i->op){
            case OP_ADD:    simd_add_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_SUB:    simd_sub_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_ISUB:   simd_subi_bmp_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            // case OP_MUL:    simd_mul_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            // case OP_DIV:    simd_div_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            // case OP_IDIV:   simd_divi_bmp_8bpc_npl  (args->imgfile, i->arg.op_const); break;

            // case OP_ADDS:   simd_adds_bmp_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            // case OP_SUBS:   simd_subs_bmp_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            // case OP_ISUBS:  simd_subis_bmp_8bpc_npl (args->imgfile, i->arg.op_const); break;

            // case OP_POW:    simd_pow_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            // case OP_LOG:    simd_log_bmp_8bpc_npl   (args->imgfile);                  break;
            // case OP_ABS:    simd_abs_bmp_8bpc_npl   (args->imgfile);                  break;
            // case OP_MIN:    simd_min_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            // case OP_MAX:    simd_max_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;

            // case OP_NEG:    simd_neg_bmp_8bpc_npl   (args->imgfile);                  break;
            case OP_GS:     simd_gs_bmp_8bpc_npl    (args->imgfile);                  break;

            // case OP_KERN:   simd_kern_bmp_8bpc_npl  (args->imgfile, i->arg.op_kern);  break;

            case OP_WR: img_fwrite(args->imgfile, i->arg.op_fileio); break;
        }
    }
}

#define rgb_ptrs ptr_r + j, ptr_g + j, ptr_b + j

// process, simd & pipeline
static void process_opt(args_t* args){
    pnode_t* start_s = args->signal_chain;
    pnode_t* end_s = args->signal_chain;
    while(start_s){
        for(size_t i = 0; i < args->imgfile->height; ++i){
            uint8_t* ptr_r = args->imgfile->imgdata._8bpc.r[i];
            uint8_t* ptr_g = args->imgfile->imgdata._8bpc.g[i];
            uint8_t* ptr_b = args->imgfile->imgdata._8bpc.b[i];

            size_t j = 0;
            for(; j < (args->imgfile->width & ~0x1F); j += 32){
                pnode_t* s = start_s;
                for(; s && OP_WR != s->op && OP_KERN != s->op; s = s->next){
                    switch(s->op){
                        case OP_ADD:    simd_add_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_SUB:    simd_sub_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_ISUB:   simd_subi_bmp_8bpc  (rgb_ptrs, s->arg.op_const); break;
                        // case OP_MUL:    simd_mul_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        // case OP_DIV:    simd_div_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        // case OP_IDIV:   simd_divi_bmp_8bpc  (rgb_ptrs, s->arg.op_const); break;

                        // case OP_ADDS:   simd_adds_bmp_8bpc  (rgb_ptrs, s->arg.op_const); break;
                        // case OP_SUBS:   simd_subs_bmp_8bpc  (rgb_ptrs, s->arg.op_const); break;
                        // case OP_ISUBS:  simd_subis_bmp_8bpc (rgb_ptrs, s->arg.op_const); break;

                        // case OP_POW:    simd_pow_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        // case OP_LOG:    simd_log_bmp_8bpc   (rgb_ptrs);                  break;
                        // case OP_ABS:    simd_abs_bmp_8bpc   (rgb_ptrs);                  break;
                        // case OP_MIN:    simd_min_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        // case OP_MAX:    simd_max_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;

                        // case OP_NEG:    simd_neg_bmp_8bpc   (rgb_ptrs);                  break;
                        case OP_GS:     simd_gs_bmp_8bpc    (rgb_ptrs);                  break;
                    }
                }
                end_s = s;
            }

        }

        if(end_s && OP_KERN == end_s->op){
            // simd_kern_bmp_8bpc_npl(args->imgfile, end_s->arg.op_kern);
        }

        if(end_s && OP_WR == end_s->op){
            img_fwrite(args->imgfile, end_s->arg.op_fileio);
        }

        start_s = end_s->next;
    }
}

uint64_t process(args_t* args){
    if(args->no_simd && args->no_pipeline){
        struct timespec start_time = timer_start();
        process_ns_np(args);
        return timer_end(start_time);
    }

    if(args->no_simd && !args->no_pipeline){
        struct timespec start_time = timer_start();
        process_ns(args);
        return timer_end(start_time);
    }

    if(!args->no_simd && args->no_pipeline){
        struct timespec start_time = timer_start();
        process_np(args);
        return timer_end(start_time);
    }

    struct timespec start_time = timer_start();
    process_opt(args);
    return timer_end(start_time);
}
