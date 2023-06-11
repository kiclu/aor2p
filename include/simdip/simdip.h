#ifndef _SIMDIP_H
#define _SIMDIP_H

// basic arithmetic operations
#include<simdip/add.h>
#include<simdip/sub.h>
#include<simdip/subi.h>
#include<simdip/mul.h>
#include<simdip/div.h>
#include<simdip/divi.h>

// basic arithmetic operations w/ saturation
#include<simdip/adds.h>
#include<simdip/subs.h>
#include<simdip/subis.h>

// 
#include<simdip/pow.h>
#include<simdip/log.h>
#include<simdip/abs.h>
#include<simdip/min.h>
#include<simdip/max.h>

// image filters
#include<simdip/neg.h>
#include<simdip/gs.h>

// kernel filter
#include<simdip/kern.h>

#include<cliparse/cliparse.h>

uint64_t process(args_t*);

#endif//_SIMDIP_H
