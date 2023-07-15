#include<cli/parse.h>

#include<string.h>
#include<stdbool.h>
#include<stdio.h>

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
        fprintf(stderr, "aor2p: error: kernel file invalid\n");
        exit(EXIT_FAILURE);
    }
    FILE* fin = fopen(filename, "r");
    if(NULL == fin){
        fprintf(stderr, "aor2p: error: kernel file not found\n");
        exit(EXIT_FAILURE);
    }

    t->arg.op_kern.kern = (float**)malloc(t->arg.op_kern.n * sizeof(float*));
    for(size_t i = 0; i < t->arg.op_kern.n; ++i){
        t->arg.op_kern.kern[i] = (float*)malloc(t->arg.op_kern.m * sizeof(float));
    }

    for(size_t i = 0; i < t->arg.op_kern.n; ++i){
        for(size_t j = 0; j < t->arg.op_kern.n; ++j){
            fscanf(fin, "%f", &t->arg.op_kern.kern[i][j]);
        }
    }
    fclose(fin);
    
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

#include<img/imgparse.h>

static void help_page(){
    printf("aor2p  v1.0\n");
    printf("Usage: ./aor2p input-file [options]\n");
    printf("\n");
    printf("Options:\n");
    printf("    -a=<const>,   --add=<const>      Add constant\n");
    printf("    -s=<const>,   --sub=<const>      Subtract constant\n");
    printf("    -is=<const>,  --isub=<const>     Subtract from constant\n");
    printf("    -m=<const>,   --mul=<const>      Multiply by constant\n");
    printf("    -d=<const>,   --div=<const>      Divide by constant\n");
    printf("    -id=<const>,  --idiv=<const>     Divide constant by pixel value\n");
    printf("\n");
    printf("    -as=<const>,  --adds=<const>     Add constant (with saturation)\n");
    printf("    -ss=<const>,  --subs=<const>     Subtract constant (with saturation)\n");
    printf("    -iss=<const>, --isubs=<const>    Subtract from constant (with saturation)\n");
    printf("\n");
    printf("    -p=<const>,   --pow=<const>      Raise every pixel to power of const.\n");
    printf("    -l, --log                        Replace every pixel with logarithm base 2 of its value\n");
    printf("    --abs                            Replace every pixel with absolute value of its value\n");
    printf("    --min=<const>                    Replace every pixel with minimum of its value and constant\n");
    printf("    --max=<const>                    Replace every pixel with maximum of its value and constant\n");
    printf("\n");
    printf("    -n,  --neg                       Apply negative filter to image\n");
    printf("    -gs, --greyscale                 Apply greyscale filter to image\n");
    printf("\n");
    printf("    -k=<file>, --kern=<file>         Apply kernel filer to image. Expects a *.kernNxM file,\n");
    printf("                                     N and M are height and width of kernel, respectively\n");
    printf("\n");
    printf("    -o=<file>                        Write to file, output file type must match input file type\n");
    printf("Optimization flags:\n");
    printf("    -s0                              No optimizations\n");
    printf("    -s1                              [Reserved for future use]\n");
    printf("    -s2                              SIMD, no pipeline\n");
    printf("    -s3                              SIMD and pipeline, default\n");
    printf("    --no-simd                        disable SIMD\n");
    printf("    --no-pipeline                    disable pipeline\n");
    printf("    --thread-count=<N>               enable multi-threading with N threads, -s3 only\n");
}

args_t* cliparse(int argc, const char** argv){
    if(argc < 2){
        help_page();
        return NULL;
    }

    // initialize args structure
    args_t* args = NULL;
    if(NULL == (args = malloc(sizeof(args_t)))){
        fprintf(stderr, "aor2p: MEM_ERROR\n");
        exit(EXIT_FAILURE);
    }

    // read input file
    args->imgfile = img_fread(argv[1]);
    if(NULL == args->imgfile){
        fprintf(stderr, "aor2p: error: input file invalid\n");
        exit(EXIT_FAILURE);
    }

    // check for valid output file
    bool output_file_bmp = false;
    bool output_file_png = false;
    for(int i = 2; i < argc; ++i){
        if(strstr(argv[i], "-o=") && strstr(argv[i], ".bmp")) output_file_bmp = true;
        if(strstr(argv[i], "-o=") && strstr(argv[i], ".png")) output_file_png = true;
    }

    if(!output_file_bmp && !output_file_png){
        fprintf(stderr, "aor2p: error: no output file specified\n");
        exit(EXIT_FAILURE);
    }

    if(output_file_bmp && output_file_png){
        fprintf(stderr, "aor2p: error: input and output file types do not match\n");
        exit(EXIT_FAILURE);
    }

    // parse all optimization level flags
    args->thread_count = 0;
    args->no_pipeline = false;
    args->no_simd = false;

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
    
    if(opt_level == -1){
        for(int i = 2; i < argc; ++i){
            if(argv[i] == strstr(argv[i], "--no-pipeline")) args->no_pipeline = true;
            if(argv[i] == strstr(argv[i], "--no-simd")) args->no_simd = true;
            if(argv[i] == strstr(argv[i], "--thread-count=") || argv[i] == strstr(argv[i], "--thread_count=")){
                if(opt_level == -1) opt_level = 3;
                if(opt_level != 3){
                    fprintf(stderr, "aor2p: warning: multi-threading support is enabled only on -s3 optimization level\n");
                }
                args->thread_count = atoi(strchr(argv[i], '=') + 1);
            }
        }
    }

    // parse all operations and create signal chain
    args->signal_chain = NULL;
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

        if(argv[i] == strstr(argv[i], "-k=") || argv[i] == strstr(argv[i], "--kern=")){
            kern_init(args->imgfile->height, args->imgfile->width);
            insert_op_kernel(&args->signal_chain, OP_KERN, strchr(argv[i], '=') + 1);
            continue;
        }

        if(argv[i] == strstr(argv[i], "-o=")){
            insert_op_fileio(&args->signal_chain, OP_WR, strchr(argv[i], '=') + 1);
            continue;
        }
        
        //fprintf(stderr, "aor2p: error: unrecognized argument %s\n", argv[i]);
        //exit(EXIT_FAILURE);
    }

#ifdef  SIMDIP_VERBOSE
    int c = 0;
    printf("======================================================================\n");
    printf("FILTERS:\n");
    printf("----------------------------------------------------------------------\n");
    for(pnode_t* i = args->signal_chain; i; i = i->next){
        switch(i->op){
            case OP_ADD:   c += printf("op_add");   break;
            case OP_SUB:   c += printf("op_sub");   break;
            case OP_ISUB:  c += printf("op_isub");  break;
            case OP_MUL:   c += printf("op_mul");   break;
            case OP_DIV:   c += printf("op_div");   break;
            case OP_IDIV:  c += printf("op_idiv");  break;

            case OP_ADDS:  c += printf("op_adds");  break;
            case OP_SUBS:  c += printf("op_subs");  break;
            case OP_ISUBS: c += printf("op_isubs"); break;

            case OP_POW:   c += printf("op_pow");   break;
            case OP_LOG:   c += printf("op_log");   break;
            case OP_ABS:   c += printf("op_abs");   break;
            case OP_MIN:   c += printf("op_min");   break;
            case OP_MAX:   c += printf("op_max");   break;

            case OP_NEG:   c += printf("op_neg");   break;
            case OP_GS:    c += printf("op_gs");    break;

            case OP_KERN:  c += printf("op_kern");  break;

            case OP_WR:    c += printf("op_wr");    break;
        }

        switch(i->type){
            case op_const:  c += printf(" %d", i->arg.op_const); break;
            case op_kern:   c += printf(" %lux%lu", i->arg.op_kern.n, i->arg.op_kern.m); break;
            case op_fileio: c += printf(" %s", i->arg.op_fileio); break;
            case op_noarg:  break;
        }
        if(i->next) printf(" | ");
        if(c > 50){ c = 0; printf("\n"); }
    }
    printf("\n");
    printf("======================================================================\n");
#endif//SIMDIP_VERBOSE

    return args;
}

static void op_kern_free(pnode_t* p){
    for(size_t i = 0; i < p->arg.op_kern.n; ++i){
        free(p->arg.op_kern.kern[i]);
    }
    free(p->arg.op_kern.kern);
}

void cliparse_free(args_t* args){
    if(NULL == args) return;

    pnode_t* p = args->signal_chain;
    for(pnode_t* i = p->next; i; i = i->next){
        if(op_kern == i->type) op_kern_free(i);
        free(p); p = i;
    }
    free(p);

    img_free(args->imgfile);
    free(args);

    kern_free();
}
