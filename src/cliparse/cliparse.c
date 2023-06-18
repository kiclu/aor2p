#include<cliparse/cliparse.h>

#include<string.h>
#include<stdbool.h>

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

#include<imgparse/imgparse.h>

args_t* cliparse(int argc, const char** argv){
    if(argc < 2) {
        // TODO: print help page
        return NULL;
    }

    // initialize args structure
    args_t* args = malloc(sizeof(args_t));

    // read input file
    args->imgfile = img_fread(argv[1]);
    if(NULL == args->imgfile){
        free(args);
        return NULL;
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
        img_free(args->imgfile);
        free(args);
        return NULL;
    }

    if(output_file_bmp && output_file_png){
        // TODO: mismatched output filetypes error
        img_free(args->imgfile);
        free(args);
        return NULL;
    }

    int opt_level = -1;
    for(int i = 2; i < argc; ++i){
        if(argv[i] == strstr(argv[i], "-s0")){
            args->no_pipeline = args->no_simd = true;
            opt_level = 0;
            break;
        }
        if(argv[i] == strstr(argv[i], "-s2")){
            args->no_pipeline = true;
            opt_level = 2;
            break;
        }
        if(argv[i] == strstr(argv[i], "-s3")){
            opt_level = 3;
            break;
        }
    }
    
    if(opt_level != -1){
        for(int i = 2; i < argc; ++i){
            if(argv[i] == strstr(argv[i], "--no-pipeline")) args->no_pipeline = true;
            if(argv[i] == strstr(argv[i], "--no-simd")) args->no_simd = true;
        }
    }

    for(int i = 2; i < argc; ++i){
        if(argv[i] == strstr(argv[i], "-a=") || argv[i] == strstr(argv[i], "--add=")){
            insert_op_const(&args->signal_chain, OP_ADD, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(argv[i] == strstr(argv[i], "-s=") || argv[i] == strstr(argv[i], "--sub=")){
            insert_op_const(&args->signal_chain, OP_SUB, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(argv[i] == strstr(argv[i], "-is=") || argv[i] == strstr(argv[i], "--isub=")){
            insert_op_const(&args->signal_chain, OP_ISUB, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(argv[i] == strstr(argv[i], "-m=") || argv[i] == strstr(argv[i], "--mul=")){
            insert_op_const(&args->signal_chain, OP_MUL, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(argv[i] == strstr(argv[i], "-d=") || argv[i] == strstr(argv[i], "--div=")){
            insert_op_const(&args->signal_chain, OP_DIV, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(argv[i] == strstr(argv[i], "-id=") || argv[i] == strstr(argv[i], "--idiv=")){
            insert_op_const(&args->signal_chain, OP_IDIV, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(argv[i] == strstr(argv[i], "-as=") || argv[i] == strstr(argv[i], "--add-saturate=")){
            insert_op_const(&args->signal_chain, OP_ADDS, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(argv[i] == strstr(argv[i], "-ss=") || argv[i] == strstr(argv[i], "--sub-saturate=")){
            insert_op_const(&args->signal_chain, OP_SUBS, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(argv[i] == strstr(argv[i], "-iss=") || argv[i] == strstr(argv[i], "--isub-saturate=")){
            insert_op_const(&args->signal_chain, OP_ISUBS, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(argv[i] == strstr(argv[i], "-p=") || argv[i] == strstr(argv[i], "--pow=")){
            insert_op_const(&args->signal_chain, OP_POW, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(argv[i] == strstr(argv[i], "-l") || argv[i] == strstr(argv[i], "--log")){
            insert_op_noarg(&args->signal_chain, OP_LOG);
            continue;
        }

        if(argv[i] == strstr(argv[i], "--abs")){
            insert_op_noarg(&args->signal_chain, OP_ABS);
            continue;
        }

        if(argv[i] == strstr(argv[i], "--min=")){
            insert_op_const(&args->signal_chain, OP_MIN, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(argv[i] == strstr(argv[i], "--max=")){
            insert_op_const(&args->signal_chain, OP_MAX, atoi(strchr(argv[i], '=') + 1));
            continue;
        }

        if(argv[i] == strstr(argv[i], "-n") || argv[i] == strstr(argv[i], "--neg")){
            insert_op_noarg(&args->signal_chain, OP_NEG);
            continue;
        }

        if(argv[i] == strstr(argv[i], "-gs") || argv[i] == strstr(argv[i], "--greyscale")){
            insert_op_noarg(&args->signal_chain, OP_GS);
            continue;
        }

        if(argv[i] == strstr(argv[i], "-k=") || argv[i] == strstr(argv[i], "--kernel=")){
            insert_op_kernel(&args->signal_chain, OP_KERN, strchr(argv[i], '=') + 1);
            continue;
        }

        if(argv[i] == strstr(argv[i], "-o=")){
            insert_op_fileio(&args->signal_chain, OP_WR, strchr(argv[i], '=') + 1);
            continue;
        }

        // TODO: handle parameter not recognized error
    }

#ifdef  SIMDIP_VERBOSE
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
#endif//SIMDIP_VERBOSE

    return args;
}

void cliparse_free(args_t* args){
    if(NULL == args) return;

    pnode_t* p = args->signal_chain;
    for(pnode_t* i = p->next; i; i = i->next){ free(p); p = i; }
    free(p);

    img_free(args->imgfile);
    free(args);
}
