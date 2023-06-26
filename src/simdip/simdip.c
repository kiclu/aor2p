#include<simdip/simdip.h>

#include<cliparse/cliparse.h>
#include<imgparse/imgparse.h>
#include<time.h>

static struct timespec timer_start(){
    struct timespec start_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
    return start_time;
}

static uint64_t timer_end(struct timespec start_time){
    struct timespec end_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
    return (end_time.tv_sec - start_time.tv_sec) * 1000000000UL + (end_time.tv_nsec - start_time.tv_nsec);;
}

// process, no simd & no pipeline
static uint64_t process_ns_np(args_t* args){
    struct timespec start_time = timer_start();
    uint64_t write_time = 0;
    for(pnode_t* i = args->signal_chain; i; i = i->next){
        switch(i->op){
            case OP_ADD:    add_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_SUB:    sub_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_ISUB:   subi_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            case OP_MUL:    mul_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_DIV:    div_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_IDIV:   divi_8bpc_npl  (args->imgfile, i->arg.op_const); break;

            case OP_ADDS:   adds_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            case OP_SUBS:   subs_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            case OP_ISUBS:  subis_8bpc_npl (args->imgfile, i->arg.op_const); break;

            case OP_POW:    pow_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_LOG:    log_8bpc_npl   (args->imgfile);                  break;
            case OP_ABS:    abs_8bpc_npl   (args->imgfile);                  break;
            case OP_MIN:    min_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_MAX:    max_8bpc_npl   (args->imgfile, i->arg.op_const); break;

            case OP_NEG:    neg_8bpc_npl   (args->imgfile);                  break;
            case OP_GS:     gs_8bpc_npl    (args->imgfile);                  break;

            case OP_KERN:   kern_8bpc_npl  (args->imgfile, i->arg.op_kern);  break;

            case OP_WR:{
                struct timespec write_start_time = timer_start();
                img_fwrite(args->imgfile, i->arg.op_fileio);
                write_time += timer_end(write_start_time);
            } break;
        }
    }
    return timer_end(start_time) - write_time;
}

// process, no simd & pipeline
static uint64_t process_ns(args_t* args){
    // TODO: implement
    return 0;
}

// process, simd & no pipeline
static uint64_t process_np(args_t* args){
    struct timespec start_time = timer_start();
    uint64_t write_time = 0;
    for(pnode_t* i = args->signal_chain; i; i = i->next){
        switch(i->op){
            case OP_ADD:    simd_add_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_SUB:    simd_sub_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_ISUB:   simd_subi_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            case OP_MUL:    simd_mul_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_DIV:    simd_div_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_IDIV:   simd_divi_8bpc_npl  (args->imgfile, i->arg.op_const); break;

            case OP_ADDS:   simd_adds_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            case OP_SUBS:   simd_subs_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            case OP_ISUBS:  simd_subis_8bpc_npl (args->imgfile, i->arg.op_const); break;

            case OP_POW:    simd_pow_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_LOG:    simd_log_8bpc_npl   (args->imgfile);                  break;
            case OP_ABS:    simd_abs_8bpc_npl   (args->imgfile);                  break;
            case OP_MIN:    simd_min_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_MAX:    simd_max_8bpc_npl   (args->imgfile, i->arg.op_const); break;

            case OP_NEG:    simd_neg_8bpc_npl   (args->imgfile);                  break;
            case OP_GS:     simd_gs_8bpc_npl    (args->imgfile);                  break;

            case OP_KERN:   simd_kern_8bpc_npl  (args->imgfile, i->arg.op_kern);  break;

            case OP_WR:{
                struct timespec write_start_time = timer_start();
                img_fwrite(args->imgfile, i->arg.op_fileio);
                write_time += timer_end(write_start_time);
            } break;
        }
    }
    return timer_end(start_time) - write_time;
}

#define rgb_ptrs ptr_r + j, ptr_g + j, ptr_b + j

// process, simd & pipeline
static uint64_t process_st(args_t* args){
    struct timespec start_time = timer_start();
    uint64_t write_time = 0;
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
                        case OP_ADD:    simd_add_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_SUB:    simd_sub_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_ISUB:   simd_subi_8bpc  (rgb_ptrs, s->arg.op_const); break;
                        case OP_MUL:    simd_mul_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_DIV:    simd_div_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_IDIV:   simd_divi_8bpc  (rgb_ptrs, s->arg.op_const); break;

                        case OP_ADDS:   simd_adds_8bpc  (rgb_ptrs, s->arg.op_const); break;
                        case OP_SUBS:   simd_subs_8bpc  (rgb_ptrs, s->arg.op_const); break;
                        case OP_ISUBS:  simd_subis_8bpc (rgb_ptrs, s->arg.op_const); break;

                        case OP_POW:    simd_pow_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_LOG:    simd_log_8bpc   (rgb_ptrs);                  break;
                        case OP_ABS:    simd_abs_8bpc   (rgb_ptrs);                  break;
                        case OP_MIN:    simd_min_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_MAX:    simd_max_8bpc   (rgb_ptrs, s->arg.op_const); break;

                        case OP_NEG:    simd_neg_8bpc   (rgb_ptrs);                  break;
                        case OP_GS:     simd_gs_8bpc    (rgb_ptrs);                  break;

                        case OP_KERN:   break;
                        case OP_WR:     break;
                    }
                }
                end_s = s;
            }

        }

        if(end_s && OP_KERN == end_s->op){
            simd_kern_8bpc_npl(args->imgfile, end_s->arg.op_kern);
        }

        if(end_s && OP_WR == end_s->op){
            struct timespec write_start_time = timer_start();
            img_fwrite(args->imgfile, end_s->arg.op_fileio);
            write_time += timer_end(write_start_time);
        }

        start_s = end_s->next;
    }

    return timer_end(start_time) - write_time;
}

#include<pthread.h>
#include<semaphore.h>

typedef struct{
    size_t thread_id;

    size_t si;
    size_t ei;
    args_t* args;

    // sychronization barriers
    pthread_barrier_t* barrier_kern;
    pthread_barrier_t* barrier_wr;
} process_worker_arg_t;

static void* process_smt_worker(void* arg){
    process_worker_arg_t* warg = (process_worker_arg_t*)arg;
    args_t* args = warg->args;

    uint64_t write_time = 0;
    
    pnode_t* start_s = args->signal_chain;
    pnode_t* end_s = args->signal_chain;
    while(start_s){
        for(size_t i = warg->si; i < warg->ei; ++i){
            uint8_t* ptr_r = args->imgfile->imgdata._8bpc.r[i];
            uint8_t* ptr_g = args->imgfile->imgdata._8bpc.g[i];
            uint8_t* ptr_b = args->imgfile->imgdata._8bpc.b[i];

            size_t j = 0;
            for(; j < (args->imgfile->width & ~0x1F); j += 32){
                pnode_t* s = start_s;
                for(; s && OP_WR != s->op && OP_KERN != s->op; s = s->next){
                    switch(s->op){
                        case OP_ADD:    simd_add_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_SUB:    simd_sub_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_ISUB:   simd_subi_8bpc  (rgb_ptrs, s->arg.op_const); break;
                        case OP_MUL:    simd_mul_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_DIV:    simd_div_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_IDIV:   simd_divi_8bpc  (rgb_ptrs, s->arg.op_const); break;

                        case OP_ADDS:   simd_adds_8bpc  (rgb_ptrs, s->arg.op_const); break;
                        case OP_SUBS:   simd_subs_8bpc  (rgb_ptrs, s->arg.op_const); break;
                        case OP_ISUBS:  simd_subis_8bpc (rgb_ptrs, s->arg.op_const); break;

                        case OP_POW:    simd_pow_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_LOG:    simd_log_8bpc   (rgb_ptrs);                  break;
                        case OP_ABS:    simd_abs_8bpc   (rgb_ptrs);                  break;
                        case OP_MIN:    simd_min_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_MAX:    simd_max_8bpc   (rgb_ptrs, s->arg.op_const); break;

                        case OP_NEG:    simd_neg_8bpc   (rgb_ptrs);                  break;
                        case OP_GS:     simd_gs_8bpc    (rgb_ptrs);                  break;

                        case OP_KERN:   break;
                        case OP_WR:     break;
                    }
                }
                end_s = s;
            }

        }

        if(end_s && OP_KERN == end_s->op){
            // wait for all other threads to finish all work before kernel operation
            pthread_barrier_wait(warg->barrier_kern);

            // kernel operation
            simd_kern_8bpc_npl_smt(
                args->imgfile,
                end_s->arg.op_kern,
                warg->si,
                warg->thread_id == args->thread_count - 1 ? warg->ei - end_s->arg.op_kern.n : warg->ei
            );

            // wait for kernel operation to finish on all threads
            pthread_barrier_wait(warg->barrier_kern);

            // swap kernel filter buffer and image data
            if(warg->thread_id == 0) simd_kswap_8bpc_npl_smt(args->imgfile);

            // wait for swap to finish
            pthread_barrier_wait(warg->barrier_kern);
        }

        if(end_s && OP_WR == end_s->op){
            if(warg->thread_id == 0){
                struct timespec write_start_time = timer_start();

                // wait for all other threads to finish all work before writing
                pthread_barrier_wait(warg->barrier_wr);

                // write
                img_fwrite(args->imgfile, end_s->arg.op_fileio);

                // wait for output to finish before continuing all threads
                pthread_barrier_wait(warg->barrier_wr);

                write_time += timer_end(write_start_time);
            }
            else{
                // wait for worker thread 0 to finish file output
                pthread_barrier_wait(warg->barrier_wr);
                pthread_barrier_wait(warg->barrier_wr);
            }
        }

        start_s = end_s->next;
    }

    uint64_t* time = (uint64_t*)malloc(sizeof(uint64_t));
    *time = write_time;

    pthread_exit((void*)time);
}


static uint64_t process_smt(args_t* args){
    // initialize worker thread synchronization barriers
    pthread_barrier_t barrier_kern;
    pthread_barrier_t barrier_wr;

    pthread_barrier_init(&barrier_kern, NULL, args->thread_count);
    pthread_barrier_init(&barrier_wr, NULL, args->thread_count);
    
    // initialize worker threads
    process_worker_arg_t* warg = (process_worker_arg_t*)malloc(args->thread_count * sizeof(process_worker_arg_t));
    for(size_t i = 0; i < args->thread_count; ++i){
        warg[i].thread_id = i;

        warg[i].si = (args->imgfile->height / args->thread_count) * i;
        warg[i].ei = (args->imgfile->height / args->thread_count) * (i+1);
        warg[i].args = args;
    
        warg[i].barrier_kern = &barrier_kern;
        warg[i].barrier_wr = &barrier_wr;
    }
    warg[args->thread_count - 1].ei = args->imgfile->height;
    
    // create worker threads
    pthread_t* pt = (pthread_t*)malloc(args->thread_count * sizeof(pthread_t));
    
    // start time measurement
    struct timespec start_time = timer_start();

    for(size_t i = 0; i < args->thread_count; ++i){
        pthread_create(&pt[i], NULL, process_smt_worker, (void*)&warg[i]);
    }
    
    // wait for all worker threads to finish and compute time taken
    uint64_t total_write_time = 0;
    for(size_t i = 0; i < args->thread_count; ++i){
        uint64_t* thread_write_time;
        pthread_join(pt[i], (void**)&thread_write_time);
        total_write_time += *thread_write_time;
        free(thread_write_time);
    }
    
    // free barriers
    pthread_barrier_destroy(&barrier_kern);
    pthread_barrier_destroy(&barrier_wr);

    free(warg);
    free(pt);

    return timer_end(start_time) - total_write_time;
}

uint64_t process(args_t* args){
    if( args->no_simd &&  args->no_pipeline) return process_ns_np(args);
    if( args->no_simd && !args->no_pipeline) return process_ns(args);
    if(!args->no_simd &&  args->no_pipeline) return process_np(args);
    return args->thread_count ? process_smt(args) : process_st(args);
}
