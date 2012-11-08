#pragma once

#include <types.h>

typedef int(* init_func_t)(void);

#define __init_code        __attribute__ ((__section__(".code.init")))
#define INIT_CALL_LEVEL(n) __attribute__ ((__section__(".Level"#n".bl1")))

#define __INIT_DEV__ INIT_CALL_LEVEL(4)

#define module_init(func) \
	static __USED__ __INIT_DEV__ init_func_t init_call_##func = func
