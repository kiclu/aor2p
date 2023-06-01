#ifndef _CLIPARSE_H
#define _CLIPARSE_H

#include<stdbool.h>

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

    // -k=filenmae, --kernel=filename
    OP_KERN
} op_t;

// int cliparse_init(int argc, const char** argv);

#endif//_CLIPARSE_H