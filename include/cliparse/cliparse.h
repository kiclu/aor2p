#ifndef _CLIPARSE_H
#define _CLIPARSE_H

#include<stdbool.h>

#include<imgparse/imgfile.h>
#include<simdip/kern.h>

typedef enum{
    // -a=const, --add=const
    OP_ADD,
    // -s=const, --sub=const
    OP_SUB,
    // -is=const, --isub=const
    OP_ISUB,
    // -m=const, --mul=const
    OP_MUL,
    // -d=const, --div=const
    OP_DIV,
    // -id=const, --idiv=const
    OP_IDIV,

    // -as=const, --add-saturate=const
    OP_ADDS,
    // -ss=const, --sub-saturate=const
    OP_SUBS,
    // -iss=const, --isub-saturate=const
    OP_ISUBS,

    // -p=const, --pow=const
    OP_POW,
    // -l=const, --log=const
    OP_LOG,
    // --abs
    OP_ABS,
    // --min=const
    OP_MIN,
    // --max=const
    OP_MAX,

    // -n, --neg
    OP_NEG,
    // -gs, --greyscale
    OP_GS,

    // -k=filename, --kernel=filename
    OP_KERN,

    // -o=filename
    OP_WR
} op_t;

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

typedef struct args{
    imgfile_t* imgfile;

    pnode_t* signal_chain;

    bool no_pipeline;
    bool no_simd;
} args_t;

args_t* cliparse(int argc, const char** argv);

#endif//_CLIPARSE_H