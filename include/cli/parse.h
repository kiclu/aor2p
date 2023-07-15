#ifndef _AOR2P_CLI_PARSE_H_
#define _AOR2P_CLI_PARSE_H_

#include<stdbool.h>

#include<img/imgfile.h>
#include<op/kern.h>

typedef enum{
    OP_ADD,
    OP_SUB,
    OP_ISUB,
    OP_MUL,
    OP_DIV,
    OP_IDIV,

    OP_ADDS,
    OP_SUBS,
    OP_ISUBS,

    OP_POW,
    OP_MIN,
    OP_MAX,
    OP_LOG,
    OP_ABS,

    OP_NEG,
    OP_GS,

    OP_KERN,

    OP_WR
} op_t;

typedef union {
    int         op_const;
    kern_t      op_kern;
    const char* op_fileio;
} op_arg_t;

typedef enum {
    op_const,
    op_kern,
    op_fileio,
    op_noarg
} optype_t;

typedef struct pnode{
    op_t            op;
    optype_t        type;
    op_arg_t        arg;
    struct pnode*   next;
} pnode_t;

typedef struct args{
    imgfile_t*  imgfile;

    pnode_t*    signal_chain;

    bool        no_pipeline;
    bool        no_simd;
    size_t      thread_count;
} args_t;

args_t* cliparse(int argc, const char** argv);
void cliparse_free(args_t* args);

#endif//_AOR2_CLI_PARSE_H_
