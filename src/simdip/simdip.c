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
static uint64_t process_ns_np(args_t* args){
    struct timespec start_time = timer_start();
    uint64_t write_time = 0;
    for(pnode_t* i = args->signal_chain; i; i = i->next){
        switch(i->op){
            case OP_ADD:    add_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_SUB:    sub_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_ISUB:   subi_bmp_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            case OP_MUL:    mul_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_DIV:    div_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_IDIV:   divi_bmp_8bpc_npl  (args->imgfile, i->arg.op_const); break;

            case OP_ADDS:   adds_bmp_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            case OP_SUBS:   subs_bmp_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            case OP_ISUBS:  subis_bmp_8bpc_npl (args->imgfile, i->arg.op_const); break;

            case OP_POW:    pow_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_LOG:    log_bmp_8bpc_npl   (args->imgfile);                  break;
            case OP_ABS:    abs_bmp_8bpc_npl   (args->imgfile);                  break;
            case OP_MIN:    min_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_MAX:    max_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;

            case OP_NEG:    neg_bmp_8bpc_npl   (args->imgfile);                  break;
            case OP_GS:     gs_bmp_8bpc_npl    (args->imgfile);                  break;

            case OP_KERN:   kern_bmp_8bpc_npl  (args->imgfile, i->arg.op_kern);  break;

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
    return 0;
}

// process, simd & no pipeline
static uint64_t process_np(args_t* args){
    struct timespec start_time = timer_start();
    uint64_t write_time = 0;
    for(pnode_t* i = args->signal_chain; i; i = i->next){
        switch(i->op){
            case OP_ADD:    simd_add_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_SUB:    simd_sub_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_ISUB:   simd_subi_bmp_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            case OP_MUL:    simd_mul_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_DIV:    simd_div_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_IDIV:   simd_divi_bmp_8bpc_npl  (args->imgfile, i->arg.op_const); break;

            case OP_ADDS:   simd_adds_bmp_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            case OP_SUBS:   simd_subs_bmp_8bpc_npl  (args->imgfile, i->arg.op_const); break;
            case OP_ISUBS:  simd_subis_bmp_8bpc_npl (args->imgfile, i->arg.op_const); break;

            case OP_POW:    simd_pow_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_LOG:    simd_log_bmp_8bpc_npl   (args->imgfile);                  break;
            case OP_ABS:    simd_abs_bmp_8bpc_npl   (args->imgfile);                  break;
            case OP_MIN:    simd_min_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;
            case OP_MAX:    simd_max_bmp_8bpc_npl   (args->imgfile, i->arg.op_const); break;

            case OP_NEG:    simd_neg_bmp_8bpc_npl   (args->imgfile);                  break;
            case OP_GS:     simd_gs_bmp_8bpc_npl    (args->imgfile);                  break;

            case OP_KERN:   simd_kern_bmp_8bpc_npl  (args->imgfile, i->arg.op_kern);  break;

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

#ifndef THREAD_COUNT
// process, simd & pipeline
static uint64_t process_opt(args_t* args){
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
                        case OP_ADD:    simd_add_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_SUB:    simd_sub_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_ISUB:   simd_subi_bmp_8bpc  (rgb_ptrs, s->arg.op_const); break;
                        case OP_MUL:    simd_mul_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_DIV:    simd_div_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_IDIV:   simd_divi_bmp_8bpc  (rgb_ptrs, s->arg.op_const); break;

                        case OP_ADDS:   simd_adds_bmp_8bpc  (rgb_ptrs, s->arg.op_const); break;
                        case OP_SUBS:   simd_subs_bmp_8bpc  (rgb_ptrs, s->arg.op_const); break;
                        case OP_ISUBS:  simd_subis_bmp_8bpc (rgb_ptrs, s->arg.op_const); break;

                        case OP_POW:    simd_pow_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_LOG:    simd_log_bmp_8bpc   (rgb_ptrs);                  break;
                        case OP_ABS:    simd_abs_bmp_8bpc   (rgb_ptrs);                  break;
                        case OP_MIN:    simd_min_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_MAX:    simd_max_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;

                        case OP_NEG:    simd_neg_bmp_8bpc   (rgb_ptrs);                  break;
                        case OP_GS:     simd_gs_bmp_8bpc    (rgb_ptrs);                  break;

                        case OP_KERN:   break;
                        case OP_WR:     break;
                    }
                }
                end_s = s;
            }

        }

        if(end_s && OP_KERN == end_s->op){
            simd_kern_bmp_8bpc_npl(args->imgfile, end_s->arg.op_kern);
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

#else

#include<pthread.h>
#include<semaphore.h>

typedef struct{
    size_t thread_id;
    size_t si;
    size_t ei;
    args_t* args;
    uint64_t time;

    sem_t* write_entry_sem;
    sem_t* write_exit_sem;
} process_worker_arg_t;

void* process_opt_mt_worker(void* arg){
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
                        case OP_ADD:    simd_add_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_SUB:    simd_sub_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_ISUB:   simd_subi_bmp_8bpc  (rgb_ptrs, s->arg.op_const); break;
                        case OP_MUL:    simd_mul_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_DIV:    simd_div_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_IDIV:   simd_divi_bmp_8bpc  (rgb_ptrs, s->arg.op_const); break;

                        case OP_ADDS:   simd_adds_bmp_8bpc  (rgb_ptrs, s->arg.op_const); break;
                        case OP_SUBS:   simd_subs_bmp_8bpc  (rgb_ptrs, s->arg.op_const); break;
                        case OP_ISUBS:  simd_subis_bmp_8bpc (rgb_ptrs, s->arg.op_const); break;

                        case OP_POW:    simd_pow_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_LOG:    simd_log_bmp_8bpc   (rgb_ptrs);                  break;
                        case OP_ABS:    simd_abs_bmp_8bpc   (rgb_ptrs);                  break;
                        case OP_MIN:    simd_min_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;
                        case OP_MAX:    simd_max_bmp_8bpc   (rgb_ptrs, s->arg.op_const); break;

                        case OP_NEG:    simd_neg_bmp_8bpc   (rgb_ptrs);                  break;
                        case OP_GS:     simd_gs_bmp_8bpc    (rgb_ptrs);                  break;

                        case OP_KERN:   break;
                        case OP_WR:     break;
                    }
                }
                end_s = s;
            }

        }

        if(end_s && OP_KERN == end_s->op){
            if(warg->thread_id == 0) simd_kern_bmp_8bpc_npl(args->imgfile, end_s->arg.op_kern);
        }

        if(end_s && OP_WR == end_s->op){
            if(warg->thread_id == 0){
                struct timespec write_start_time = timer_start();
                for(size_t i = 0; i < THREAD_COUNT - 1; ++i) sem_wait(warg->write_entry_sem);
                img_fwrite(args->imgfile, end_s->arg.op_fileio);
                for(size_t i = 0; i < THREAD_COUNT - 1; ++i) sem_post(warg->write_exit_sem);
                write_time += timer_end(write_start_time);
            }
            else{
                sem_post(warg->write_entry_sem);
                sem_wait(warg->write_exit_sem);
            }
        }

        start_s = end_s->next;
    }

    uint64_t* time = (uint64_t*)malloc(sizeof(uint64_t));
    *time = write_time;

    pthread_exit((void*)time);
}

static uint64_t process_opt_mt(args_t* args){
    struct timespec start_time = timer_start();

    sem_t write_entry_sem;
    sem_t write_exit_sem;
    sem_init(&write_entry_sem, 0, THREAD_COUNT - 1);
    sem_init(&write_exit_sem, 0, 0);

    process_worker_arg_t warg[THREAD_COUNT];
    for(size_t i = 0; i < THREAD_COUNT; ++i){
        warg[i].thread_id = i;
        warg[i].si = (args->imgfile->height / THREAD_COUNT) * i;
        warg[i].ei = (args->imgfile->height / THREAD_COUNT) * (i+1);
        warg[i].args = args;
        warg[i].write_entry_sem = &write_entry_sem;
        warg[i].write_exit_sem = &write_exit_sem;
    }
    warg[THREAD_COUNT-1].ei = args->imgfile->height;

    pthread_t pt[THREAD_COUNT];
    for(size_t i = 0; i < THREAD_COUNT; ++i){
        pthread_create(&pt[i], NULL, process_opt_mt_worker, (void*)&warg[i]);
    }
    
    uint64_t total_write_time = 0;
    for(size_t i = 0; i < THREAD_COUNT; ++i){
        uint64_t* thread_write_time;
        pthread_join(pt[i], (void**)&thread_write_time);
        total_write_time += *thread_write_time;
        free(thread_write_time);
    }

    return timer_end(start_time) - total_write_time;
}
#endif//THREAD_COUNT

uint64_t process(args_t* args){
    if( args->no_simd &&  args->no_pipeline) return process_ns_np(args);
    if( args->no_simd && !args->no_pipeline) return process_ns(args);
    if(!args->no_simd &&  args->no_pipeline) return process_np(args);
#ifdef THREAD_COUNT
    return process_opt_mt(args);
#else
    return process_opt(args);
#endif//THREADCOUNT
}
