#ifndef _AOR2P_IP_H_
#define _AOR2P_IP_H_

// basic arithmetic operations
#include<op/add.h>
#include<op/sub.h>
#include<op/subi.h>
#include<op/mul.h>
#include<op/div.h>
#include<op/divi.h>

// basic arithmetic operations w/ saturation
#include<op/adds.h>
#include<op/subs.h>
#include<op/subis.h>

// 
#include<op/pow.h>
#include<op/log.h>
#include<op/abs.h>
#include<op/min.h>
#include<op/max.h>

// image filters
#include<op/neg.h>
#include<op/gs.h>

// kernel filter
#include<op/kern.h>

#include<op/reg.h>

#include<cli/parse.h>

uint64_t process(args_t*);

#endif//_AOR2P_IP_H_
