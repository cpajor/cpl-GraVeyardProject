#ifndef CPL_THREADS_H
#define CPL_THREADS_H
#ifdef __cplusplus
extern "C" {
#endif
#include "cpl.h"

typedef void (*thr_func_t)(int id);

#ifndef CPL_MAX_THREADS
#define CPL_MAX_THREADS 4
#endif

void cplthr_set(char id, thr_func_t func);

void cplthr_temp(voidfunc_t t);

#ifdef __cplusplus
}
#endif
#endif // !CPL_THREADS_H