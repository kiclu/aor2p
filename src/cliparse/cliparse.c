#include<cliparse/cliparse.h>

#include<string.h>
#include<stdbool.h>

#include<simdip/kern.h>

typedef union {
    int op_const;
    kern_t op_kern;
    const char* op_fileio;
} op_arg_t;

typedef enum {
    op_const,
    op_kern,
    op_fileio,
    op_noarg
} optype_t;

typedef struct pnode{
    op_t op;
    optype_t type;
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

static void insert_op_const(pnode_t** chain, op_t op, int arg){
    pnode_t* t = malloc(sizeof(pnode_t));
    t->op = op;
    t->type = op_const;
    t->arg.op_const = arg;
    t->next = NULL;

    if(NULL == *chain){ *chain = t; return; }
    pnode_t* i;
    for(i = *chain; i->next; i = i->next);
    i->next = t;
}

static void insert_op_kernel(pnode_t** chain, op_t op, const char* filename){
    pnode_t* t = malloc(sizeof(pnode_t));
    t->op = op;
    t->type = op_kern;
    t->next = NULL;

    sscanf(filename, "%*[^.].kern%lux%lu", &t->arg.op_kern.n, &t->arg.op_kern.m);
    if(t->arg.op_kern.n == 0 || t->arg.op_kern.m == 0){
        free(t);
        // TODO: handle kernel file format invalid
        return;
    }
    FILE* fin = fopen(filename, "r");
    if(NULL == fin){
        printf("aor2p: error: kernel file not found");
        free(t);
        return;
        // TODO: handle kernel file not found
    }

    t->arg.op_kern.kern = (int8_t**)malloc(t->arg.op_kern.n * sizeof(int8_t*));
    for(size_t i = 0; i < t->arg.op_kern.n; ++i){
        t->arg.op_kern.kern[i] = (int8_t*)malloc(t->arg.op_kern.m * sizeof(int8_t));
    }

    for(size_t i = 0; i < t->arg.op_kern.n; ++i){
        for(size_t j = 0; j < t->arg.op_kern.n; ++j){
            fscanf(fin, "%hhd", &t->arg.op_kern.kern[i][j]);
        }
    }
    
    if(NULL == *chain){ *chain = t; return; }
    pnode_t* i;
    for(i = *chain; i->next; i = i->next);
    i->next = t;
}

static void insert_op_fileio(pnode_t** chain, op_t op, const char* filename){
    pnode_t* t = malloc(sizeof(pnode_t));
    t->op = op;
    t->type = op_fileio;
    t->arg.op_fileio = filename;
    t->next = NULL;

    if(NULL == *chain){ *chain = t; return; }
    pnode_t* i;
    for(i = *chain; i->next; i = i->next);
    i->next = t;
}

static void insert_op_noarg(pnode_t** chain, op_t op){
    pnode_t* t = malloc(sizeof(pnode_t));
    t->op = op;
    t->type = op_noarg;
    t->next = NULL;

    if(NULL == *chain){ *chain = t; return; }
    pnode_t* i;
    for(i = *chain; i->next; i = i->next);
    i->next = t;
}

int cliparse_init(int argc, const char** argv){
    if(argc < 2) {
        // TODO: print help page
        return -1;
    }

    // check for valid output file
    bool output_file_bmp = false;
    bool output_file_png = false;
    for(int i = 2; i < argc; ++i){
        if(strstr(argv[i], "-o=") && strstr(argv[i], ".bmp")) output_file_bmp = true;
        if(strstr(argv[i], "-o=") && strstr(argv[i], ".png")) output_file_png = true;
    }

    if(!output_file_bmp && !output_file_png){
        // TODO: no output file error
        return -1;
    }

    if(output_file_bmp && output_file_png){
        // TODO: mismatched output filetypes error
        return -1;
    }

    bool no_pipeline = false;
    bool no_simd = false;

    for(int i = 2; i < argc; ++i){
        if(strstr(argv[i], "--no-pipeline")) no_pipeline = true;
        if(strstr(argv[i], "--no-simd")) no_simd = true;
    }


    args_t* args = malloc(sizeof(args_t));

    for(int i = 2; i < argc; ++i){
        if(strstr(argv[i], "-a=") || strstr(argv[i], "--add=")){
            insert_op_const(&args->signal_chain, OP_ADD, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(strstr(argv[i], "-s=") || strstr(argv[i], "--sub=")){
            insert_op_const(&args->signal_chain, OP_SUB, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(strstr(argv[i], "-is=") || strstr(argv[i], "--isub=")){
            insert_op_const(&args->signal_chain, OP_ISUB, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(strstr(argv[i], "-m=") || strstr(argv[i], "--mul=")){
            insert_op_const(&args->signal_chain, OP_MUL, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(strstr(argv[i], "-d=") || strstr(argv[i], "--div=")){
            insert_op_const(&args->signal_chain, OP_DIV, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(strstr(argv[i], "-id=") || strstr(argv[i], "--idiv=")){
            insert_op_const(&args->signal_chain, OP_IDIV, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(strstr(argv[i], "-as=") || strstr(argv[i], "--add-saturate=")){
            insert_op_const(&args->signal_chain, OP_ADDS, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(strstr(argv[i], "-ss=") || strstr(argv[i], "--sub-saturate=")){
            insert_op_const(&args->signal_chain, OP_SUBS, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(strstr(argv[i], "-iss=") || strstr(argv[i], "--isub-saturate=")){
            insert_op_const(&args->signal_chain, OP_ISUBS, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(strstr(argv[i], "-p=") || strstr(argv[i], "--pow=")){
            insert_op_const(&args->signal_chain, OP_POW, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(strstr(argv[i], "-l=") || strstr(argv[i], "--log=")){
            insert_op_const(&args->signal_chain, OP_LOG, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(strstr(argv[i], "--abs")){
            insert_op_noarg(&args->signal_chain, OP_ABS);
            continue;
        }

        if(strstr(argv[i], "--min=")){
            insert_op_const(&args->signal_chain, OP_MIN, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(strstr(argv[i], "--max=")){
            insert_op_const(&args->signal_chain, OP_MAX, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(strstr(argv[i], "-n") || strstr(argv[i], "--neg")){
            insert_op_noarg(&args->signal_chain, OP_NEG);
            continue;
        }

        if(strstr(argv[i], "-gs") || strstr(argv[i], "--greyscale")){
            insert_op_noarg(&args->signal_chain, OP_GS);
            continue;
        }

        if(strstr(argv[i], "-k=") || strstr(argv[i], "--kernel=")){
            insert_op_kernel(&args->signal_chain, OP_KERN, strchr(argv[i], '=') + 1);
            continue;
        }

        if(strstr(argv[i], "-o=")){
            insert_op_fileio(&args->signal_chain, OP_WR, strchr(argv[i], '=') + 1);
            continue;
        }

        // TODO: handle parameter not recognized error
    }

    for(pnode_t* i = args->signal_chain; i; i = i->next){
        switch(i->op){
            case OP_ADD:   printf("op_add");   break;
            case OP_SUB:   printf("op_sub");   break;
            case OP_ISUB:  printf("op_isub");  break;
            case OP_MUL:   printf("op_mul");   break;
            case OP_DIV:   printf("op_div");   break;
            case OP_IDIV:  printf("op_idiv");  break;

            case OP_ADDS:  printf("op_adds");  break;
            case OP_SUBS:  printf("op_subs");  break;
            case OP_ISUBS: printf("op_isubs"); break;

            case OP_POW:   printf("op_pow");   break;
            case OP_LOG:   printf("op_log");   break;
            case OP_ABS:   printf("op_abs");   break;
            case OP_MIN:   printf("op_min");   break;
            case OP_MAX:   printf("op_max");   break;

            case OP_NEG:   printf("op_neg");   break;
            case OP_GS:    printf("op_gs");    break;

            case OP_KERN:  printf("op_kern");  break;

            case OP_WR:    printf("op_wr");    break;
        }

        switch(i->type){
            case op_const:  printf(" %d\n", i->arg.op_const); break;
            case op_kern:   printf(" %lux%lu\n", i->arg.op_kern.n, i->arg.op_kern.m); break;
            case op_fileio: printf(" %s\n", i->arg.op_fileio); break;
            case op_noarg:  printf("\n"); break;
        }
    }
    return 0;
}
