#ifndef MEMP_TYPE_H
#define MEMP_TYPE_H

#ifdef __cplusplus
extern "C"{
#endif

typedef T_VOID* (*Memp_a)(T_UINT32 tag, T_UINT32 size);
typedef F_RET   (*Memp_f)();

/* Memp memerory control point */
typedef void* Memp;

extern F_RET memp_create
(
    Memp      *pps_memp,
    T_UINT32   ul_init_size,
    T_UINT32   ul_grow_size
);
extern T_VOID* memp_alloc
(
    Memp     ps_memp,
    T_UINT32 ul_size
);

//extern F_RET memp_free(Memp memp);

#ifdef __cplusplus
}
#endif
#endif /* MEMP_TYPE_H */
