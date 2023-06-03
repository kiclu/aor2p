#include<cliparse/cliparse.h>

#include<string.h>
#include<stdbool.h>

#include<simdip/kern.h>

typedef union {
    int op_const;
    kern_t op_kern;
} op_arg_t;

typedef struct pnode{
    op_t op;
    op_arg_t arg;
    struct pnode* next;
} pnode_t;

typedef struct {
    int argc;
    const char** argv;

    bool no_pipeline;
    bool no_simd;

    pnode_t* signal_chain;
} args_t;

static void insert(pnode_t** chain, op_t op, int arg){
    if(NULL == *chain){
        *chain = malloc(sizeof(pnode_t));
        (*chain)->op = op;
        // (*chain)->arg
        (*chain)->next = NULL;
    }
    pnode_t* i;
    for(i = *chain; i->next; i = i->next);
    i = i->next = malloc(sizeof(pnode_t));
    i->op = op;
    i->next = NULL;
}

int cliparse_init(int argc, const char** argv){
    if(argc < 2) {
        // TODO: print help page
        return -1;
    }

    bool no_pipeline = false;
    bool no_simd = false;

    bool output_file = false;
    for(int i = 2; i < argc; ++i){
        if(strstr(argv[i], "-o=")) output_file = true;
        if(strstr(argv[i], "--no-pipeline")) no_pipeline = true;
        if(strstr(argv[i], "--no-simd")) no_simd = true;
    }

    if(!output_file){
        // TODO: no output file error
        return -1;
    }

    args_t* args = malloc(sizeof(args_t));

    for(int i = 2; i < argc; ++i){
        if(strstr(argv[i], "-a=") || strstr(argv[i], "--add=")){
            insert(&args->signal_chain, OP_ADD, atoi(strchr(argv[i], '=')));
        }

        if(strstr(argv[i], "-s=") || strstr(argv[i], "--sub=")){
            insert(&args->signal_chain, OP_SUB, atoi(strchr(argv[i], '=')));
        }

        if(strstr(argv[i], "-is=") || strstr(argv[i], "--isub=")){
            insert(&args->signal_chain, OP_ADD, atoi(strchr(argv[i], '=')));
        }
    }

    for(pnode_t* i = args->signal_chain; i; i = i->next){
        switch(i->op){
            case OP_ADD: printf("op_add\n"); break;
            case OP_SUB: printf("op_sub\n"); break;
            case OP_ISUB: printf("op_isub\n"); break;
        }
    }
    return 0;
}