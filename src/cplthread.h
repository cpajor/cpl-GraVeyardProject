#ifndef CPL_THREADS_H
#define CPL_THREADS_H
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*thr_func_t)();

#ifndef CPL_MAX_THREADS
#define CPL_MAX_THREADS 3
#endif

void cplthr_set(char id, thr_func_t func);

#ifdef __cplusplus
}
#endif
#endif // !CPL_THREADS_H