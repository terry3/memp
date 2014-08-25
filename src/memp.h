#ifndef MEMP_TYPE_H
#define MEMP_TYPE_H

#ifdef __cplusplus
extern "C"{
#endif

typedef T_VOID* (*Memp_a)(T_UINT32 tag, T_UINT32 size);
typedef F_RET   (*Memp_f)();

/* Memp memerory control point */
typedef void* Memp;
/* typedef struct _Memp */
/* { */
/*     Memp_a alloc; /\* alloc memory function *\/ */
/*     Memp_f free;  /\* free memory function *\/ */
/* }Memp; */
extern F_RET memp_init();
extern F_RET memp_create(Memp *memp);
extern T_VOID* memp_alloc(Memp memp, T_UINT32 size, T_UINT32 tag);
extern F_RET memp_free(Memp memp);

#ifdef __cplusplus
}
#endif
#endif /* MEMP_TYPE_H */
